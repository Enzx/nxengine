#include "render/render_system.h"

#include <filesystem>
#include <glm/ext/matrix_transform.hpp>

#include "render/opengl/model.h"
#include "render/opengl/opengl_render_api.h"
#include "window/window_system.h"

render::render_system::render_system()
{
}

void render::render_system::on_create(nx::service::locator<>* locator)
{
    NX_LOG_DEBUGF("render_system::on_create");
    const auto window_service = locator->get<window::window_system>();
    window_ = window_service->get_current_window();
    window_->events->subscribe<window::events::resize>(&render_system::on_window_resize, this);

    api_ = nx::create_ref<opengl_render_api>();
    renderer_ = nx::create_ref<nx::render::renderer>(api_);
    renderer_->init();


    renderer_->set_clear_color(0.2f, 0.3f, 0.3f, 1.0f);

    NX_LOG_TRACE("opengl_render_system::on_create");
    camera_ = nx::render::camera();
    camera_.update_projection_matrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    camera_.set_position(glm::vec3(0.0f, 0.0f, 10.0f));
    camera_.look_at(glm::vec3(0.0f, 0.0f, 0.0f));

    // build and compile shader program
    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path assets_path = cwd / "assets";
    const std::filesystem::path assets_path_shaders = assets_path / "shaders";
    const std::filesystem::path vertex_shader_path = assets_path_shaders / "default.vert";
    const std::filesystem::path fragment_shader_path = assets_path_shaders / "default.frag";

    NX_LOG_TRACE("Compile Shader Program");
    our_shader_ = api_->create_shader();
    our_shader_->compile(vertex_shader_path.string(), fragment_shader_path.string());
    NX_LOG_TRACE("Loading Model");
    our_model_ = nx::create_ref<model>((assets_path / "models" / "backpack.obj").string());
}

void render::render_system::on_window_resize(const window::events::resize& event)
{
    camera_.update_projection_matrix(45.0f,
        static_cast<float>(event.width) / static_cast<float>(event.height), 0.1f, 100.0f);

    renderer_->on_window_resize(event.width, event.height);
}

void render::render_system::update()
{
    renderer_->begin_scene(camera_);
    our_shader_->bind();
    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    our_shader_->set_mat4("model", model);

    for (const auto& mesh : our_model_->meshes_)
    {
        renderer_->submit(our_shader_, mesh.vertex_array_, model);
    }
}
