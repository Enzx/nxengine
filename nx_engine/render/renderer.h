#pragma once
#include <glm/glm.hpp>

#include "camera.h"
#include "render_api.h"
#include "render_command.h"
#include "shader.h"
#include "vertex_array.h"
#include "base/nx_pch.h"

namespace nx::render
{
    class renderer
    {
    public:
        renderer(const ref<render_api>& api ) { api_ = api;}
        void init();
        void shutdown() const;
        void begin_scene(const camera& camera) const;
        void end_scene();
        void submit(const ref<shader>& shader,
                    const ref<vertex_array>& vertex_array,
                    const glm::mat4& transform = glm::mat4(1.0f)) const;

        void on_window_resize(uint32_t width, uint32_t height) const;
        void set_clear_color(float r, float g, float b, float a) const;

    private:
        struct scene_data
        {
            glm::mat4 projection_matrix;
            glm::mat4 view_matrix;
        };

        scope<scene_data> scene_data_;
        ref<render_command> render_command_;
        ref< render_api> api_;
    };
}
