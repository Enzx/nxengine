#pragma once
#include "render/render_command.h"

class opengl_render_command final : public nx::render::render_command
{
public:
    opengl_render_command(const opengl_render_command& other) = delete;
    opengl_render_command(opengl_render_command&& other) noexcept = delete;
    opengl_render_command& operator=(const opengl_render_command& other) = delete;
    opengl_render_command& operator=(opengl_render_command&& other) noexcept = delete;
    
    opengl_render_command() = default;
    void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;
    void clear() const override;
    void set_clear_color(float r, float g, float b, float a) const override;
    void draw_indexed(const nx::ref<nx::render::vertex_array>& vertex_array, uint32_t index_count) const override;
    ~opengl_render_command() override;
};
