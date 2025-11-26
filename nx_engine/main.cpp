#define GLFW_INCLUDE_NONE
#include <csignal>
#include <filesystem>
#include <iostream>

#include "imgui.h"
#include "event/event_system.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "input/glfw_input_system.h"
#include "input/glfw_keyboard_binding.h"
#include "render/opengl/opengl_render_system.h"
#include "window/glfw_window_system.h"
#include "window/window_interface.h"
#include "window/window_events.h"

std::shared_ptr<window_interface> main_window;
bool running = true;

void on_window_close(const window::events::close& event)
{
    if (event.window_id != main_window->get_id()) return;
    std::cout << "Window closed\n";
    running = false;
}



void handle_signal(int signal)
{
    if (signal == SIGINT)
        std::cout << "[SIGINT] application terminated signal\n";
    running = false;
}

int main()
{
    std::cout << "[[Started]]\n";
    if (signal(SIGINT, handle_signal) == SIG_ERR)
    {
        std::cerr << "Failed to register signal handler\n";
        return -1;
    }

    nx::service::locator<> services;
    const auto window_system = services.add<window::window_system, window::glfw_window_system>();
    main_window = window_system->create_window(640, 480, "Hello World");
    window_system->set_current_window(main_window);
    main_window->events->subscribe<window::events::close>(&on_window_close);
    const auto input_system = services.add<glfw_input_system>();
    const auto renderer = services.add<render::render_system>();



    const auto close_input_action =
        std::make_shared<nx::input::input_action>(new glfw_keyboard_binding(nx::input::key_code::escape),"close");


    input_system->add_input_action(close_input_action);

    while (running)
    {
        input_system->update();
        renderer->update();
        window_system->update();

        if (close_input_action->get_state() == nx::input::key_state::press)
            main_window->close();
    }

    window_system->terminate();

    std::cout << "[[Finished]]\n";
    return 0;
}
