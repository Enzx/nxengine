#include "glfw_window.h"
#include "GLFW/glfw3.h"

glfw_window::glfw_window(int width, int height, std::string& title) : i_window(width, height, title)
{

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window_ == nullptr) {
        //Error
        return;
    }
    glfwMakeContextCurrent(window_);
}

glfw_window::~glfw_window()
{
    glfwDestroyWindow(window_);
    window_ = nullptr;
}

void glfw_window::show() override
{
    glfwShowWindow(window_);
}

void glfw_window::hide() override
{
    glfwHideWindow(window_);
}