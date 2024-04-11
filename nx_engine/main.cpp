#define GLFW_INCLUDE_NONE

#include <iostream>

#include "data_types/service_locator/locator.h"
#include "event/event_system.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "platform/window/glfw_window_system.h"
#include "window/window_system.h"
#include "window/interface_window.h"
#include "window/window_events.h"


std::shared_ptr<interface_window> main_window;
bool running = true;

void on_window_close(const window::events::window_close& event)
{
    if (event.window_id != main_window->get_id())
        return;
    std::cout << "Window closed\n";
    running = false;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 


int main()
{
    std::cout << "[[Started]]\n";

    service::locator services;
    services.add<window::glfw_window_system>();
    const auto window_system = services.get<window::window_system>();
    window_system->initialize();
    main_window = window_system->create_window(640, 480, "Hello World");
    main_window->events->subscribe<window::events::window_close>(&on_window_close);
    event::event_system events;
    // std::cout << "IMGUI Version: " << ImGui::GetVersion();
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 640, 480);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glfwSetFramebufferSizeCallback((GLFWwindow*)main_window->get_raw_pointer(), framebuffer_size_callback);  

    while (running)
    {
        window_system->update();
    }
    window_system->terminate();
    std::cout << "[[Finished]]\n";
    return 0;
}
