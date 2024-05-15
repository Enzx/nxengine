#pragma once
#include <memory>
#include <string>
#include "../event/event_system.h"

class interface_window;

namespace window
{
    class window_system
    {
    public:
        virtual ~window_system() = default;
        virtual void terminate() = 0;
        virtual void update() = 0;


        virtual std::shared_ptr<interface_window> create_window(int width, int height, std::string&& title) = 0;
        virtual void destroy_window(std::shared_ptr<interface_window>) = 0;

        [[nodiscard]] std::shared_ptr<interface_window> get_current_window() const { return current_window_; }
        void virtual set_current_window(const std::shared_ptr<interface_window>& window) { current_window_ = window; }

        std::shared_ptr<event::event_system> events;

    protected:
        std::shared_ptr<interface_window> current_window_;
    };
}
