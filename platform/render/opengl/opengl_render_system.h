#pragma once

#include "opengl_shader.h"
#include "render/render_system.h"
#include <glm/vec3.hpp>

#include "camera.h"
#include "model.h"
#include "opengl_render_api.h"
#include "opengl_render_command.h"
#include "glad/glad.h"
#include "input/input_action.h"
#include "data_types/service_locator/locator.h"




class opengl_render_system final : public render::render_system
{
public:
    opengl_render_system();

    opengl_render_system(const opengl_render_system& other) = delete;
    opengl_render_system(opengl_render_system&& other) noexcept = delete;
    opengl_render_system& operator=(const opengl_render_system& other) = delete;
    opengl_render_system& operator=(opengl_render_system&& other) noexcept = delete;
    ~opengl_render_system() override;
    void update() override;

    void on_create(nx::service::locator<>* locator);

private:
    opengl_shader our_shader_{};

    Camera camera_{glm::vec3(0.0f, 0.0f, 3.0f)};
    std::shared_ptr<nx::input::input_action> right_input_;
    std::shared_ptr<nx::input::input_action> left_input_;
    std::shared_ptr<nx::input::input_action> rotate_right_;
    std::shared_ptr<nx::input::input_action> rotate_left_;

    model* our_model;
    opengl_render_api api_{};
    opengl_render_command command_{};
};
