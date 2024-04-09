#include "glfw_window.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "../../window/window_events.h"

window::glfw_window::glfw_window(const int width, const int height, std::string& title) : interface_window(
    width, height, title)
{
    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window_ == nullptr)
    {
        //Error
        std::cout << "Could not create glfw window";
        return;
    }
    glfwMakeContextCurrent(window_);
}

window::glfw_window::~glfw_window()
{
    glfwDestroyWindow(window_);
    window_ = nullptr;
}

void window::glfw_window::show()
{
    glfwShowWindow(window_);
}

void window::glfw_window::hide()
{
    glfwHideWindow(window_);
}

void window::glfw_window::update()
{
    glfwSwapBuffers(window_);
    if (glfwWindowShouldClose(window_))
    {
        events->publish(events::window_close{window_id_});
    }
}

void* window::glfw_window::get_raw_pointer()
{
    return window_;
}
