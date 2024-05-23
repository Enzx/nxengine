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


namespace service::policy
{
    class thread_safe;
}

void opengl_render_system::on_create(service::locator<>* locator)
{
    LOG_DEBUGF("opengl_render_system::on_create");
    // right_input_ = std::make_shared<
    //     input::input_action>(input::device_type::keyboard, input::key_code::d, "Move_Right");
    // left_input_ = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::a, "Move_Left");
    // rotate_right_ = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::e,
    //                                                       "Rotate_Right");
    // rotate_left_ = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::q,
    //                                                      "Rotate_Left");
    // const auto input_system = locator->get<platform::input::glfw_input>();
    // input_system->add_input_action(right_input_);
    // input_system->add_input_action(left_input_);
    // input_system->add_input_action(rotate_right_);
    // input_system->add_input_action(rotate_left_);
    
    LOG_TRACE("opengl_render_system::on_create");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to initialize GLAD");
        return;
    }
    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl_message_callback, nullptr);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 640, 480);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //  mesh_ = new opengl_mesh();


    // build and compile shader program
    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path assets_path = cwd / "assets";
    const std::filesystem::path assets_path_shaders = assets_path / "shaders";
    const std::filesystem::path vertex_shader_path = assets_path_shaders / "default.vert";
    const std::filesystem::path fragment_shader_path = assets_path_shaders / "default.frag";

    LOG_TRACE("Compile Shader Program");
    our_shader_.compile(vertex_shader_path.c_str(), fragment_shader_path.c_str());
    LOG_TRACE("Loading Model");
    our_model = new model((assets_path / "models" / "backpack.obj").string().c_str());

    // camera
 

    // draw wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void opengl_render_system::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    our_shader_.use();
    GL_CHECK_ERROR();

    glm::mat4 projection = glm::perspective(glm::radians(camera_.Zoom), 640.0f / 480.f, 0.1f, 100.0f);
    glm::mat4 view = camera_.GetViewMatrix();

    our_shader_.set_mat4("projection", projection);
    our_shader_.set_mat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // it's a bit too big for our scene, so scale it down
    our_shader_.set_mat4("model", model);
    GL_CHECK_ERROR();

    our_model->draw(our_shader_);
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
        LOG_ERRORF("OpenGL Error: {}", error);
    }
}


opengl_render_system::opengl_render_system()
{
}

opengl_render_system::~opengl_render_system()
{
    delete our_model;
}
