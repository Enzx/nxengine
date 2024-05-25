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
    vertex_array_->bind();
}

void opengl_mesh::unbind() const
{
    vertex_array_->unbind();
}


void opengl_mesh::setup_mesh()
{
    // create buffers/arrays
    vertex_array_ = std::make_shared<opengl::opengl_vertex_array>();
    vertex_buffer_ = std::make_shared<opengl::vertex_buffer>((float*)&vertices[0],
                                                             vertices.size() * sizeof(Vertex));
    index_buffer_ = std::make_shared<opengl::index_buffer>(&indices[0], indices.size());

    render::buffer_layout layout = {
        {render::buffer_data_type::float3, "aPos"},
        {render::buffer_data_type::float3, "aNormal"},
        {render::buffer_data_type::float2, "aTexCoords"},
        {render::buffer_data_type::float3, "aTangent"},
        {render::buffer_data_type::float3, "aBitangent"},
        {render::buffer_data_type::int4, "bone_ids"},
        {render::buffer_data_type::int4, "weights"}
    };

    vertex_buffer_->set_layout(layout);
    index_buffer_->set_layout(layout);

    vertex_array_->add_vertex_buffer(vertex_buffer_);
    vertex_array_->set_index_buffer(index_buffer_);
    
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
    vertex_array_->bind();
    GL_CHECK_ERROR();

    glDrawElements(GL_TRIANGLES,   index_buffer_->get_count() , GL_UNSIGNED_INT, nullptr);
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
