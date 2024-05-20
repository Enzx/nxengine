﻿#pragma once
#include "../../input/input_system.h"
#include "../window/glfw_window.h"
#include "../../data_types/service_locator/locator.h"
namespace platform::input
{
    class glfw_input final : public ::input::input_system
    {
    public:
        glfw_input() = default;
        glfw_input(const glfw_input& other) = delete;
        glfw_input(glfw_input&& other) noexcept = delete;
        glfw_input& operator=(const glfw_input& other) = delete;
        glfw_input& operator=(glfw_input&& other) noexcept = delete;

        void update() override;
        void add_input_action(const std::shared_ptr<::input::input_action>& action) override;
        void remove_input_action(const std::shared_ptr<::input::input_action>& action) override;
        ~glfw_input() override;
        void on_create(const service::locator* locator);

    private:

        GLFWwindow* window_ = nullptr;
    };
}
