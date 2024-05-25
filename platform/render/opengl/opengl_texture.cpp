#include "opengl_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>

#include "log/logger.h"

std::vector< std::string> opengl_texture::our_loaded_textures;
void opengl_texture::load(const std::string& pth)
{
   
    path = pth;
    const std::string fpath = path;
    if (std::ranges::find(our_loaded_textures, fpath) != our_loaded_textures.end())
    {
        return;
    }
    else
    {
        our_loaded_textures.push_back(fpath);
    }
    stbi_set_flip_vertically_on_load(true);
    void* data = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
    if (data)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        if (channels_ == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (channels_ == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            NX_LOG_ERROR("Unsupported number of channels in texture");
            return;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        NX_LOG_INFOF("Texture loaded: {}", path);
    }
    else
    {
        NX_LOG_ERROR("Failed to load texture");
        return;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

void opengl_texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
    GLenum error = glGetError();
    if (error == GL_INVALID_OPERATION)
    {
        NX_LOG_ERRORF(" opengl_texture::bind Error: {} path: {}, id: {}", error, path, id);
        __debugbreak();
    }
}

void opengl_texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

opengl_texture::~opengl_texture()
{
    glDeleteTextures(1, &id);

}
