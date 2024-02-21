#include "glfw_window.h"
#include "GLFW/glfw3.h"
#include <iostream>
glfw_window::glfw_window(int width, int height, std::string& title) : interface_window(width, height, title)
{

    window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window_ == nullptr) {
        //Error
        std::cout << "Colud not create glfw window";
        return;
    }
    glfwMakeContextCurrent(window_);
}

glfw_window::~glfw_window()
{
    glfwDestroyWindow(window_);
    window_ = nullptr;
}

void glfw_window::show() 
{
    glfwShowWindow(window_);
}

void glfw_window::hide()
{
    glfwHideWindow(window_);
}

void glfw_window::update()
{
    glfwSwapBuffers(window_);
}

void* glfw_window::get_raw_pointer()
{
    return window_;
}
