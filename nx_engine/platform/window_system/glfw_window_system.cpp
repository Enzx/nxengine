#include "glfw_window_system.h"
#include "glfw_window.h"
#include "GLFW/glfw3.h"

void glfw_window_system::initialize()
{
    if(glfwInit() == false)
    {
        //Error
        return;
    }
}

void glfw_window_system::terminate()
{
    glfwTerminate();
}

std::shared_ptr<i_window> glfw_window_system::create_window(int width, int height, std::string& title)
{
    return std::make_shared<glfw_window>(width, height, title);
}

