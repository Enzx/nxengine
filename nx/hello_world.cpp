#define GLFW_INCLUDE_NONE

#include <iostream>
#include "GLFW/glfw3.h"

int main(int argc, char** argv)
{
    std::cout<<"Hello World!"<<std::endl;
    if(glfwInit() == false)
    {
       std::cout << "glfwInit() failed" << std::endl;
       return -1;
    }
    
     GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
     if(window == NULL)
     {
        std::cout << "glfwCreateWindow() failed" << std::endl;
        glfwTerminate();
        return -1;
     }
     glfwMakeContextCurrent(window);
     while(!glfwWindowShouldClose(window))
     {
        glfwSwapBuffers(window);
        glfwPollEvents();
     }
     glfwTerminate();
    return 0;
}
