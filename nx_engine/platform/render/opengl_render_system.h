#pragma once

#include "opengl_shader.h"
#include "opengl_texture.h"
#include "../../render/render_system.h"
#include <glm/vec3.hpp>

#include "camera.h"
#include "model.h"
#include "opengl_mesh.h"
#include "glad/glad.h"
#include "../../input/input_action.h"
#include "../../data_types/service_locator/locator.h"


inline void APIENTRY opengl_message_callback(GLenum source,
                                             GLenum type,
                                             GLuint id,
                                             GLenum severity,
                                             GLsizei length,
                                             const GLchar* message,
                                             const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "",
            type, severity, message);
}

class opengl_render_system final : public render_system
{
public:
    opengl_render_system();

    opengl_render_system(const opengl_render_system& other) = delete;
    opengl_render_system(opengl_render_system&& other) noexcept = delete;
    opengl_render_system& operator=(const opengl_render_system& other) = delete;
    opengl_render_system& operator=(opengl_render_system&& other) noexcept = delete;
    ~opengl_render_system() override;
    void update() override;

    void on_create(const service::locator* locator);

private:
    opengl_shader our_shader_{};

    Camera camera_{glm::vec3(0.0f, 0.0f, 3.0f)};
    std::shared_ptr<input::input_action> right_input_;
    std::shared_ptr<input::input_action> left_input_;
    std::shared_ptr<input::input_action> rotate_right_;
    std::shared_ptr<input::input_action> rotate_left_;

    model* our_model;
};
