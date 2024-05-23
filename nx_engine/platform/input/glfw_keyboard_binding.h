#pragma once
#include "../../input/input_binding.h"
#include <GLFW/glfw3.h>

class glfw_keyboard_binding final : public input::keyboard_binding
{
public:
    glfw_keyboard_binding(const glfw_keyboard_binding& other) = default;
    glfw_keyboard_binding(glfw_keyboard_binding&& other) noexcept = default;
    glfw_keyboard_binding& operator=(const glfw_keyboard_binding& other) = default;
    glfw_keyboard_binding& operator=(glfw_keyboard_binding&& other) noexcept = default;

    explicit glfw_keyboard_binding(const input::key_code& key_code,
                           const input::key_modifiers& mods = input::key_modifiers::none) :
        keyboard_binding(key_code, mods),
        window_(glfwGetCurrentContext())
    {
    }

    void update() override;
    ~glfw_keyboard_binding() override;

private:
    GLFWwindow* window_ = nullptr;
};
