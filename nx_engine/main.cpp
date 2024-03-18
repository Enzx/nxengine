#define GLFW_INCLUDE_NONE

#include <iostream>

#include "data_types/service_locator/locator.h"
#include "window_system/window_system.h"
#include "platform/window_system/glfw_window_system.h"


int main()
{
    service::locator services;
    services.add<glfw_window_system>();
    const auto window_system = services.get<window_system::window_system>();
    window_system->initialize();
    window_system->create_window(640, 480, "Hello World");


    /*  if (glfwInit() == false) {
        std::cout << "glfwInit() failed" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (window == NULL) {
        std::cout << "glfwCreateWindow() failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();*/

    while (true)
    {
        window_system->update();
    }
    services.get<window_system::window_system>()->terminate();
    return 0;
}
