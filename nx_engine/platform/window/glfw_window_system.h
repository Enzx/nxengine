#pragma once
#include "window/window_system.h"
#include "window/window_events.h"
#include "data_types/service_locator/locator.h"
#include <vector>


namespace window
{
    class glfw_window_system : public window_system
    {
    public:
        glfw_window_system() = default;
        ~glfw_window_system() override = default;

        glfw_window_system(const glfw_window_system& other) = delete;
        glfw_window_system(glfw_window_system&& other) noexcept = delete;
        glfw_window_system& operator=(const glfw_window_system& other) = delete;
        glfw_window_system& operator=(glfw_window_system&& other) noexcept = delete;

        void on_create(const service::locator<>* locator);
        void terminate() override;
        void update() override;
        void on_window_close(const events::close& event) const;
        std::shared_ptr<interface_window> create_window(int width, int height, std::string&& title) override;
        void destroy_window(std::shared_ptr<interface_window>) override;
        void set_current_window(const std::shared_ptr<interface_window>& window) override;


    private:
        std::vector<std::shared_ptr<interface_window>> windows_;
        static void on_glfw_error(int error, const char* description);

    };
}
