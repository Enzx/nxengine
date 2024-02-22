#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"

#include <iostream>

#include "data_types/service_locator/interface_service.h"
#include "data_types/service_locator/locator.h"
#include "window_system/window_system.h"
#include "platform/window_system/glfw_window_system.h"

class test_service : public service::interface_service {
int _id = 0;
public:
    test_service(int id = 0) : _id(id)
    {
        std::cout << "test_service created" << std::endl;
    }

    virtual ~test_service() override
    {
        std::cout << "test_service destroyed" << std::endl;
    }

    void test()
    {
        std::cout << "test_service::test()::id::" << _id << std::endl;
    }
};

int main()
{
    service::locator service;
    service.add<test_service>(test_service(5));
    service.get<test_service>()->test();
    service.remove<test_service>();

    service.add<glfw_window_system>();

    service.get<window_system::window_system>()->initialize();
    std::string title = "Hello World";
    service.get<window_system::window_system>()->create_window(640, 480, title);

    

    std::cout << "Hello World!" << std::endl;
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

    while (true) {
        service.get<window_system::window_system>()->update();
    }
    service.get<window_system::window_system>()->terminate();
    return 0;
}
