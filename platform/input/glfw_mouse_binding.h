#pragma once
#include "input/input_binding.h"
#include "GLFW/glfw3.h"

class glfw_mouse_binding final : public nx::input::mouse_binding
{
public:
    explicit glfw_mouse_binding(const nx::input::mouse_button& mouse_button)
        : mouse_binding(mouse_button),
          window_(glfwGetCurrentContext())
    {
    }

    void update() override;
    ~glfw_mouse_binding() override;

private:
    GLFWwindow* window_;
};
