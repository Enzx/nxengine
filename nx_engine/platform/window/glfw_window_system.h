#pragma once
#include "../../window/window_system.h"
#include "../../window/window_events.h"
#include <vector>


namespace window
{
    class glfw_window_system : public window_system
    {
    public:
        //constructor
        glfw_window_system() = default;
        //destructor
        ~glfw_window_system() override = default;

        glfw_window_system(const glfw_window_system& other) = delete;
        glfw_window_system(glfw_window_system&& other) noexcept = delete;
        glfw_window_system& operator=(const glfw_window_system& other) = delete;
        glfw_window_system& operator=(glfw_window_system&& other) noexcept = delete;

        void initialize() override;
        void terminate() override;
        void update() override;
        void on_window_close(const events::window_close& event) const;
        std::shared_ptr<interface_window> create_window(int width, int height, std::string&& title) override;
        void destroy_window(std::shared_ptr<interface_window>) override;

    private:
        std::vector<std::shared_ptr<interface_window>> windows_;
    };
}
