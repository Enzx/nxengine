#pragma once
#include "camera.h"
#include "renderer.h"
#include "render_api.h"
#include "render_command.h"
#include "base/nx_pch.h"
#include "window/window_events.h"
#include "window/window_interface.h"
#include "shader.h"
#include "render/opengl/model.h"

namespace render
{
    class render_system
    {
    public:
        render_system();
        virtual ~render_system() = default;


        virtual void on_create(nx::service::locator<>* locator);
        virtual void on_window_resize(const window::events::resize& event);
        virtual void update();

    private:
        nx::ref<window_interface> window_{};
        nx::render::camera camera_;
        nx::ref<nx::render::shader> our_shader_{};
        nx::ref<model> our_model_;
        nx::ref<nx::render::render_api> api_;
        nx::ref<nx::render::renderer> renderer_;
    };
}
