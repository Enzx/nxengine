#pragma once
#include "glfw_mouse.h"
#include "data_types/service_locator/locator.h"
#include "input/input_system.h"

class glfw_input_system final : public input::input_system
{
public:
    glfw_input_system() = default;
    glfw_input_system(const glfw_input_system& other) = delete;
    glfw_input_system(glfw_input_system&& other) noexcept = delete;
    glfw_input_system& operator=(const glfw_input_system& other) = delete;
    glfw_input_system& operator=(glfw_input_system&& other) noexcept = delete;

    void on_create(service::locator<>*)
     {
         mouse_  = std::make_unique<glfw_mouse>();
     }

     ~glfw_input_system() override
     {
         mouse_.reset();
     }

 private:
     std::unique_ptr<glfw_mouse> mouse_ = nullptr;
};
