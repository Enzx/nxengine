#include "renderer.h"

#include "render/opengl/opengl_render_api.h"

void nx::render::renderer::init() 
{
    render_command_ = api_->create_render_command();
    scene_data_ = create_scope<scene_data>();
    api_->init();
    

}

void nx::render::renderer::shutdown() const
{
     api_->shutdown();
}

void nx::render::renderer::begin_scene(const camera& camera) const
{
    scene_data_->projection_matrix = camera.get_projection_matrix();
    scene_data_->view_matrix = camera.get_view_matrix();
    render_command_->clear();

}

void nx::render::renderer::end_scene()
{
     
}

void nx::render::renderer::submit(const ref<shader>& shader, const ref<vertex_array>& vertex_array,
                      const glm::mat4& transform) const
{
    shader->set_mat4("projection", scene_data_->projection_matrix);
    shader->set_mat4("view", scene_data_->view_matrix);
    shader->set_mat4("model", transform);
    render_command_->draw_indexed(vertex_array, vertex_array->get_index_buffer()->get_count());
}

void nx::render::renderer::on_window_resize(const uint32_t width, const uint32_t height) const
{

    render_command_->set_viewport(0, 0, width, height);
}

void nx::render::renderer::set_clear_color(const float r, const float g, const float b, const float a) const
{
    render_command_->set_clear_color(r, g, b, a);
}
