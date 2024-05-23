#pragma once
#include "input/mouse.h"
#include "log/logger.h"
#include "GLFW/glfw3.h"


class glfw_mouse final : public input::mouse
{
public:
    glfw_mouse(const glfw_mouse& other) = delete;
    glfw_mouse(glfw_mouse&& other) noexcept = delete;
    glfw_mouse& operator=(const glfw_mouse& other) = delete;
    glfw_mouse& operator=(glfw_mouse&& other) noexcept = delete;

    glfw_mouse()
    {
        LOG_TRACE("glfw_mouse::glfw_mouse()");
        glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
        glfwSetScrollCallback(glfwGetCurrentContext(), scroll_callback);
    }

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        screen_position_ = glm::vec2(xpos, ypos);
    }

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        scroll_offset_ = glm::vec2(xoffset, yoffset);
    }

    ~glfw_mouse() override
    {
        
    }
};
