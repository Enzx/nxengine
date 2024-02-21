#pragma once
#include "../../window_system/i_window.h"
#include "GLFW/glfw3.h"

class glfw_window : public i_window
{
public:
    glfw_window() = default;
    glfw_window(int width, int height, std::string& title);
    ~glfw_window() override;

    void show() override;
    void hide() override;
private:
    GLFWwindow* window_ = nullptr;
    
};
