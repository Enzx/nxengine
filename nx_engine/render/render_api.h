#pragma once
#include "render_command.h"
#include "shader.h"

namespace nx::render
{
    enum class render_backend
    {
        none = 0,
        opengl,
        vulkan,
        directx
    };

    class render_api
    {
    public:
        render_api() = default;
        render_api(const render_api& other) = default;
        render_api(render_api&& other) noexcept = default;
        render_api& operator=(const render_api& other) = default;
        render_api& operator=(render_api&& other) noexcept = default;

        virtual ~render_api() = default;
        [[nodiscard]] virtual render_backend get_api() const = 0;

        virtual void init() = 0;
        virtual void shutdown() = 0;

        virtual ref<render_command> create_render_command() = 0;
        virtual ref<shader> create_shader() = 0;
    };
}
