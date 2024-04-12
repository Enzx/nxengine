#include "glfw_window_system.h"
#include "glfw_window.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "../../window/window_events.h"


void window::glfw_window_system::on_glfw_error(int error, const char* description)
{
    std::cout << "Error: " << error << " " << description << '\n';
}

void window::glfw_window_system::on_create(const service::locator* locator)
{
    if (glfwInit() == false)
    {
        std::cout << "Failed to initialize the glfw system";
    }
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 4);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwSetErrorCallback(&glfw_window_system::on_glfw_error);
}

void window::glfw_window_system::terminate()
{
    for (const auto& window : windows_)
    {
        destroy_window(window);
    }
    glfwTerminate();
}

void window::glfw_window_system::update()
{
    current_window_->update();
    glfwPollEvents();
}

void window::glfw_window_system::on_window_close(const event::close& event) const
{
    events->publish(event);
}

std::shared_ptr<interface_window> window::glfw_window_system::create_window(int width, int height, std::string&& title)
{
    std::shared_ptr<interface_window> window = std::make_shared<glfw_window>(width, height, title);
    window->events->subscribe<event::close>(&glfw_window_system::on_window_close, this);


    windows_.push_back(window);
    return window;
}

void window::glfw_window_system::destroy_window(const std::shared_ptr<interface_window> window)
{
    const auto win = static_cast<GLFWwindow*>(window->get_raw_pointer());
    const auto it = std::ranges::find(windows_, window);
    windows_.erase(it);
    glfwDestroyWindow(win);
}

void window::glfw_window_system::set_current_window(const std::shared_ptr<interface_window>& window)
{
    window_system::set_current_window(window);
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(window->get_raw_pointer()));
}
