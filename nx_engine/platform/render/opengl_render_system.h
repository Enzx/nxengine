#pragma once
#include "opengl_shader.h"
#include "opengl_texture.h"
#include "../../render/render_system.h"
#include <glm/vec3.hpp>

#include "model.h"
#include "opengl_mesh.h"

namespace service
{
    class locator;
}

class opengl_render_system final : public render_system
{
public:
    opengl_render_system() = default;

    opengl_render_system(const opengl_render_system& other) = delete;
    opengl_render_system(opengl_render_system&& other) noexcept = delete;
    opengl_render_system& operator=(const opengl_render_system& other) = delete;
    opengl_render_system& operator=(opengl_render_system&& other) noexcept = delete;
    ~opengl_render_system() override;
    void update() override;

    void on_create(const service::locator* locator);

private:
    opengl_texture texture1_{};
    opengl_texture texture2_{};
    opengl_shader our_shader_{};
    glm::vec3 camera_pos_{};
    glm::vec3 camera_target_{};
    glm::vec3 camera_direction_{};
    glm::vec3 up_{};
    glm::vec3 camera_right_{};
    glm::vec3 camera_up_{};
    glm::vec3 camera_front_{};
    float camera_speed_ = 0.05f;

    model* our_model;
};
