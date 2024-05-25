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
    [[nodiscard]] render_backend get_api() const
    {
        return api_;
    }

    void set_api(const render_backend backend)
    {
        api_ = backend;
    }

    void init()
    {
        api_ = render_backend::opengl;
    }
    void shutdown()
    {
        api_ = render_backend::none;
    }
    
    
private:
    render_backend api_ = render_backend::none;
};
