#include "opengl_render_system.h"

#include <filesystem>
#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "opengl_shader.h"
#include "../../log/logger.h"
#include "GLFW/glfw3.h"


void opengl_render_system::on_create(const service::locator* locator)
{
    LOG_INFO("opengl_render_system::on_create");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to initialize GLAD");
        return;
    }
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

    our_shader_ = opengl_shader(vertex_shader_path.c_str(), fragment_shader_path.c_str());
     our_model = new model((assets_path / "models" / "nanosuit.obj").string().c_str());
    
    // camera
    camera_pos_ = glm::vec3(0.0f, 0.0f, 5.0f);
    camera_target_ = glm::vec3(0.0f, 0.0f, 0.0f);
    camera_direction_ = glm::normalize(camera_pos_ - camera_target_);
    up_ = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_right_ = glm::normalize(glm::cross(up_, camera_direction_));
    camera_up_ = glm::cross(camera_direction_, camera_right_);
    camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
    camera_speed_ = 0.05f;

    // draw wireframe
    //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void opengl_render_system::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1_.id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2_.id);
    if (glGetError() == GL_INVALID_OPERATION)
    {
        std::cout << "GL_INVALID_OPERATION\n";
    }
    our_shader_.use();

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.f, 0.1f, 100.0f);

    camera_direction_ = glm::normalize(camera_pos_ - camera_target_);
    camera_right_ = glm::normalize(glm::cross(up_, camera_direction_));
    camera_up_ = glm::cross(camera_direction_, camera_right_);
    camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);

    // if (right_input_action->get_state() == input::key_state::press)
    //   camera_pos_ -= glm::normalize(glm::cross(camera_front_, camera_up_)) * camera_speed_;
    // if (left_input_action->get_state() == input::key_state::press)
    //   camera_pos_ += glm::normalize(glm::cross(camera_front_, camera_up_)) * camera_speed_;

    view = glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);

    our_shader_.set_mat4("projection", projection);
    our_shader_.set_mat4("view", view);
    our_model->draw(our_shader_);
    if (glGetError() == GL_INVALID_OPERATION)
    {
        std::cout << "GL_INVALID_OPERATION\n";
    }
}


opengl_render_system::~opengl_render_system()
{
    delete our_model;
}
