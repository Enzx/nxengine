#include "opengl_vertex_array.h"
#include "glad/glad.h"

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

opengl::opengl_vertex_array::opengl_vertex_array()
{
    glCreateVertexArrays(1, &id_);
}

opengl::opengl_vertex_array::~opengl_vertex_array()
{
    glDeleteVertexArrays(1, &id_);
}

void opengl::opengl_vertex_array::bind() const
{
    glBindVertexArray(id_);
}

void opengl::opengl_vertex_array::unbind() const
{
    glBindVertexArray(0);
}

void opengl::opengl_vertex_array::add_vertex_buffer(const std::shared_ptr<render::vertex_buffer>& vertex_buffer)
{
    bind();
    vertex_buffer->bind();
    
    const auto& layout = vertex_buffer->get_layout();
    DEBUG_ASSERT(!layout.get_elements().empty(), "Vertex buffer layout is empty");
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
    vertex_buffers_.push_back(vertex_buffer);
}

void opengl::opengl_vertex_array::set_index_buffer(const std::shared_ptr<render::index_buffer>& index_buffer)
{
    bind();
    index_buffer->bind();
    index_buffer_ = index_buffer;
}
