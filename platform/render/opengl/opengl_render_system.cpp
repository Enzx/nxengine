#include "opengl_render_system.h"

#include <filesystem>
#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "opengl_shader.h"
#include "log/logger.h"
#include "GLFW/glfw3.h"
#include "render/camera.h"
#include "window/glfw_window_system.h"


namespace service::policy
{
    class thread_safe;
}

void opengl_render_system::on_create(nx::service::locator<>* locator)
{
    NX_LOG_DEBUGF("opengl_render_system::on_create");
    const auto window_service = locator->get<window::glfw_window_system>();
    window_ = window_service->get_current_window();
    window_->events->subscribe<window::events::resize>(&opengl_render_system::on_window_resize, this);
    api_.init();

    command_.set_clear_color(0.2f, 0.3f, 0.3f, 1.0f);

    NX_LOG_TRACE("opengl_render_system::on_create");
    camera_ = nx::render::camera();
    camera_.update_projection_matrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    camera_.set_position(glm::vec3(10.0f, 0.0f, 10.0f));
    camera_.look_at(glm::vec3(0.0f, 0.0f, 0.0f));
     
    //  mesh_ = new opengl_mesh();


    // build and compile shader program
    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path assets_path = cwd / "assets";
    const std::filesystem::path assets_path_shaders = assets_path / "shaders";
    const std::filesystem::path vertex_shader_path = assets_path_shaders / "default.vert";
    const std::filesystem::path fragment_shader_path = assets_path_shaders / "default.frag";

    NX_LOG_TRACE("Compile Shader Program");
    our_shader_.compile(vertex_shader_path.c_str(), fragment_shader_path.c_str());
    NX_LOG_TRACE("Loading Model");
    our_model = new model((assets_path / "models" / "backpack.obj").string());

    // camera


    // draw wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void opengl_render_system::on_window_resize(const window::events::resize& event)
{
    camera_.update_projection_matrix(45.0f, event.width /event.height, 0.1f, 100.0f);

    command_.set_viewport(0, 0, event.width, event.height);
}

void opengl_render_system::update()
{
    command_.clear();
    our_shader_.use();
    GL_CHECK_ERROR();

    const glm::mat4 projection =  camera_. get_projection_matrix();
    const glm::mat4 view = camera_.get_view_matrix();

    our_shader_.set_mat4("projection", projection);
    our_shader_.set_mat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // it's a bit too big for our scene, so scale it down
    our_shader_.set_mat4("model", model);
    GL_CHECK_ERROR();

    // our_model->draw(our_shader_);
    for (const auto& mesh : our_model->meshes_)
    {
        command_.draw_indexed(mesh.vertex_array_, 0);
    }

    // if(right_input_->get_state() == input::key_state::press)
    // {
    //      camera_.ProcessKeyboard(Camera_Movement::RIGHT, 0.1f);
    // }
    // if(left_input_->get_state() == input::key_state::press)
    // {
    //     camera_.ProcessKeyboard(Camera_Movement::LEFT, 0.1f);
    // }

    GLenum error = glGetError();
    if (error == GL_INVALID_OPERATION)
    {
        NX_LOG_ERRORF("OpenGL Error: {}", error);
    }
}


opengl_render_system::opengl_render_system()
{
    our_model = nullptr;
}

opengl_render_system::~opengl_render_system()
{
    delete our_model;
}
