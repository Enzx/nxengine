#pragma once
#include "../../window_system/window_system.h"

class glfw_window_system : public window_system::window_system
{
public:
    //constructor
    glfw_window_system() = default;
    //destructor
    ~glfw_window_system() override = default;

    void initialize() override;
    void terminate() override;
    std::shared_ptr<i_window> create_window(int width, int height, std::string& title) override;
    void destroy_window() override;
};
