#include "glfw_keyboard_binding.h"
#include <GLFW/glfw3.h>

void glfw_keyboard_binding::update()
{
    triggered_ = false;
    current_state_ = input::key_state::none;
    switch (glfwGetKey(window_, static_cast<int>(key)))
    {
    case GLFW_PRESS:
        current_state_ = input::key_state::press;
        break;
    case GLFW_RELEASE:
        current_state_ = input::key_state::release;
        break;
    case GLFW_REPEAT:
        current_state_ = input::key_state::hold;
        break;
    default:
        break;
    }
    if (current_state_ == target_state_)
    {
        triggered_ = true;
    }
}

glfw_keyboard_binding::~glfw_keyboard_binding()
{
    window_ = nullptr;
}
