#define GLFW_INCLUDE_NONE

#include <iostream>

#include "data_types/service_locator/locator.h"
#include "event/event_system.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "platform/window/glfw_window_system.h"
#include "window/interface_window.h"
#include "window/window_events.h"
#include "platform/input/glfw_input.h"


std::shared_ptr<interface_window> main_window;
bool running = true;

void on_window_close(const window::event::close& event)
{
    if (event.window_id != main_window->get_id())
        return;
    std::cout << "Window closed\n";
    running = false;
}


void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}


int main()
{
    std::cout << "[[Started]]\n";

    service::locator services;
    const auto window_system = services.add<window::glfw_window_system>();
    main_window = window_system->create_window(640, 480, "Hello World");
    window_system->set_current_window(main_window);
    main_window->events->subscribe<window::event::close>(&on_window_close);
    
    const auto input_system = services.add<input::glfw_input>();
    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 640, 480);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(main_window->get_raw_pointer()), framebuffer_size_callback);

    const auto action = std::make_shared<input::input_action>(
        input::device_type::keyboard,
        input::key_code::escape,
        "Close_Window");
    input_system->add_input_action(action);
    while (running)
    {
        window_system->update();
        input_system->update();
        if (action->get_state() == input::key_state::press)
            main_window->close();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    window_system->terminate();
    std::cout << "[[Finished]]\n";
    return 0;
}
