#include "renderer.h"

void renderer::init() const
{
}

void renderer::shutdown() const
{
}

void renderer::begin_scene(const camera& camera) const
{
    scene_data_->view_projection_matrix = camera.get_projection_matrix();
}

void renderer::end_scene()
{
}

void renderer::submit(const nx::ref<shader>& shader, const nx::ref<nx::render::vertex_array>& vertex_array,
                      const glm::mat4& transform) const
{
    shader->bind();
    shader->set_mat4("view_projection", scene_data_->view_projection_matrix);
    shader->set_mat4("model", transform);
    vertex_array->bind();
    render_command_->draw_indexed(vertex_array, vertex_array->get_index_buffer()->get_count());
}

void renderer::on_window_resize(const uint32_t width, const uint32_t height) const
{
    render_command_->set_viewport(0, 0, width, height);
}
