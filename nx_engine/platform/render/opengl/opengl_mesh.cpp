#include "opengl_mesh.h"
#include <glad/glad.h>

#include "opengl_texture.h"
#include "log/logger.h"

opengl_mesh::opengl_mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setup_mesh();
}


void opengl_mesh::bind() const
{
    glBindVertexArray(vao_);
}

void opengl_mesh::unbind() const
{
    glBindVertexArray(0);
}

GLenum shader_data_type_to_opengl(render::buffer_data_type type)
{
    switch (type)
    {
    case render::buffer_data_type::float1: return GL_FLOAT;
    case render::buffer_data_type::float2: return GL_FLOAT;
    case render::buffer_data_type::float3: return GL_FLOAT;
    case render::buffer_data_type::float4: return GL_FLOAT;
    case render::buffer_data_type::mat3: return GL_FLOAT;
    case render::buffer_data_type::mat4: return GL_FLOAT;
    case render::buffer_data_type::int1: return GL_INT;
    case render::buffer_data_type::int2: return GL_INT;
    case render::buffer_data_type::int3: return GL_INT;
    case render::buffer_data_type::int4: return GL_INT;
    case render::buffer_data_type::bool1: return GL_BOOL;
    case render::buffer_data_type::bool2: return GL_BOOL;
    case render::buffer_data_type::bool3: return GL_BOOL;
    case render::buffer_data_type::bool4: return GL_BOOL;
    case render::buffer_data_type::none: LOG_ERROR("NONE buffer data type: none");
    
    }
    return GL_FLOAT;
}

void opengl_mesh::setup_mesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    vertex_buffer_ = std::make_unique<opengl::vertex_buffer>((float*)&vertices[0],
                                                             vertices.size() * sizeof(Vertex));
    index_buffer_ = std::make_unique<opengl::index_buffer>(&indices[0], indices.size());

    render::buffer_layout layout = {
        {render::buffer_data_type::float3, "aPos"},
        {render::buffer_data_type::float3, "aNormal"},
        {render::buffer_data_type::float2, "aTexCoords"},
        {render::buffer_data_type::float3, "aTangent"},
        {render::buffer_data_type::float3, "aBitangent"},
        {render::buffer_data_type::int4, "bone_ids"},
        {render::buffer_data_type::float4, "weights"}
    };

    int index = 0;
    for (const auto& element : layout.get_elements())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.get_component_count(),
                              shader_data_type_to_opengl(element.get_type()),
                              element.get_normalized() ? GL_TRUE : GL_FALSE,
                              layout.get_stride(), (const void*)element.get_offset());
        index++;
    }

    
    GL_CHECK_ERROR();
}

void opengl_mesh::draw(opengl_shader& shader) const
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        //  now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.id, (name + number).c_str()), i);
        GL_CHECK_ERROR();

        //   and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
        GL_CHECK_ERROR();
    }

    // draw mesh
    glBindVertexArray(vao_);
    GL_CHECK_ERROR();

    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    GL_CHECK_ERROR();

    glBindVertexArray(0);
    GL_CHECK_ERROR();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
    GL_CHECK_ERROR();
}

opengl_mesh::~opengl_mesh()
{
    // LOG_DEBUGF("Destroying mesh with vao: {} vbo: {}, ebo: {}", vao_, vbo_, ebo_);
    // glDeleteVertexArrays(1, &vao_);
    // glDeleteBuffers(1, &vbo_);
    // glDeleteBuffers(1, &ebo_);
}
