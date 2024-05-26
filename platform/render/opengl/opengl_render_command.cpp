#include "opengl_render_command.h"

#include "glad/glad.h"

void opengl_render_command::set_viewport(const uint32_t x, const uint32_t y,
                                         const uint32_t width, const uint32_t height) const
{
    glViewport(x, y, width, height);
}

void opengl_render_command::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void opengl_render_command::set_clear_color(const float r, const float g, const float b, const float a) const
{
    glClearColor(r, g, b, a);
}

void opengl_render_command::draw_indexed(const nx::ref<nx::render::vertex_array>& vertex_array,
                                         const uint32_t index_count) const
{
    vertex_array->bind();
    const uint32_t count = index_count ? index_count : vertex_array->get_index_buffer()->get_count();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

opengl_render_command::~opengl_render_command()
{
    NX_LOG_TRACE("opengl_render_command::~opengl_render_command");
}
