#pragma once


namespace render
{
    class render_system
    {
    public:
        render_system() = default;
        virtual ~render_system() = default;
        render_system(const render_system& other) = delete;
        render_system(render_system&& other) noexcept = delete;
        render_system& operator=(const render_system& other) = delete;
        render_system& operator=(render_system&& other) noexcept = delete;

    protected:
        virtual void update() = 0;
    };
}
