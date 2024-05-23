#include "buffers.h"
#include "glad/glad.h"

opengl::vertex_buffer::vertex_buffer(float* vertices, uint32_t size)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

opengl::vertex_buffer::~vertex_buffer()
{
    glDeleteBuffers(1, &id_);
}

void opengl::vertex_buffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void opengl::vertex_buffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//=================================================================================================
// index buffer
//=================================================================================================

opengl::index_buffer::index_buffer(uint32_t* indices, uint32_t count): count_(count)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

opengl::index_buffer::~index_buffer()
{
    glDeleteBuffers(1, &id_);
}

void opengl::index_buffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void opengl::index_buffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
