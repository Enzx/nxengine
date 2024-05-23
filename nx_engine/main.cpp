#define GLFW_INCLUDE_NONE
#define ASSIMP_STATIC
#include <csignal>
#include <iostream>
#include <filesystem>

#include "imgui.h"
#include "data_types/service_locator/locator.h"
#include "event/event_system.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "platform/window/glfw_window_system.h"
#include "window/interface_window.h"
#include "window/window_events.h"


#include "platform/input/glfw_input_system.h"
#include "platform/input/glfw_keyboard_binding.h"
#include "platform/render/opengl/opengl_render_system.h"

std::shared_ptr<interface_window> main_window;
bool running = true;

void on_window_close(const window::events::close& event)
{
    if (event.window_id != main_window->get_id()) return;
    std::cout << "Window closed\n";
    running = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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

    service::locator<> services;
    const auto window_system = services.add<window::glfw_window_system>();
    main_window = window_system->create_window(640, 480, "Hello World");
    window_system->set_current_window(main_window);
    main_window->events->subscribe<window::events::close>(&on_window_close);
    const auto input_system = services.add<glfw_input_system>();
    const auto renderer = services.add<opengl_render_system>();


    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(main_window->get_raw_pointer()), framebuffer_size_callback);

    const auto close_input_action =
        std::make_shared<input::input_action>(new glfw_keyboard_binding(input::key_code::escape),"close");


    input_system->add_input_action(close_input_action);

    while (running)
    {
        input_system->update();
        renderer->update();
        window_system->update();

        if (close_input_action->get_state() == input::key_state::press)
            main_window->close();
    }

    window_system->terminate();

    std::cout << "[[Finished]]\n";
    return 0;
}
