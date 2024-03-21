#define GLFW_INCLUDE_NONE

#include <iostream>

#include "data_types/service_locator/locator.h"
#include "event/event_system.h"
#include "window/window_system.h"
#include "platform/window/glfw_window_system.h"

class player
{
public:
    static void on_endgame(const int& score)
    {
        std::cout << "Game over with score: " << score << "\n";
    }
};


int main()
{
    service::locator services;
    services.add<window::glfw_window_system>();
    const auto window_system = services.get<window::window_system>();
    window_system->initialize();
    window_system->create_window(640, 480, "Hello World");

    event::event_system events;
    player p {};
    events.subscribe<int, ::player>(&player::on_endgame);
    events.publish(10);


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
    services.get<window::window_system>()->terminate();
    return 0;
}
