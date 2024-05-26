#pragma once

#include "base/nx_pch.h"
#include "vertex_array.h"

namespace nx::render
{
    class render_command
    {
    public:
        render_command() = default;
        render_command(const render_command& other) = delete;
        render_command(render_command&& other) noexcept = delete;
        render_command& operator=(const render_command& other) = delete;
        render_command& operator=(render_command&& other) noexcept = delete;
        
        virtual ~render_command() = default;
        virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const = 0;
        virtual void clear() const = 0;
        virtual void set_clear_color(float r, float g, float b, float a) const = 0;
        virtual void draw_indexed(const ref<vertex_array>& vertex_array, uint32_t index_count = 0) const = 0;
    };
}
