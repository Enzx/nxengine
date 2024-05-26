#pragma once


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
    render_api(const render_api& other) = delete;
    render_api(render_api&& other) noexcept = delete;
    render_api& operator=(const render_api& other) = delete;
    render_api& operator=(render_api&& other) noexcept = delete;
    
    virtual ~render_api() = default;
    [[nodiscard]] virtual  render_backend get_api() const = 0;

    virtual void init() = 0; 
    virtual void shutdown() = 0;
    
};
