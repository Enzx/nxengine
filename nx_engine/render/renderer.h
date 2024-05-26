#pragma once
#include <glm/glm.hpp>

#include "camera.h"
#include "render_command.h"
#include "shader.h"
#include "vertex_array.h"
#include "base/nx_pch.h"

class renderer
{
public:
    void init() const;
    void shutdown() const;
    void begin_scene(const camera& camera) const;
    void end_scene();
    void submit(const nx::ref<shader>& shader,
                const nx::ref<nx::render::vertex_array>& vertex_array,
                const glm::mat4& transform = glm::mat4(1.0f)) const;

    void on_window_resize(uint32_t width, uint32_t height) const;

private:
    struct scene_data
    {
        glm::mat4 view_projection_matrix;
    };

    nx::scope<scene_data> scene_data_;
    nx::scope<nx::render::render_command> render_command_;
};
