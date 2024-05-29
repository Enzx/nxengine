#pragma once
#include <memory>
#include <string>
#include "event/event_system.h"

class window_interface;

namespace window
{
    class window_system
    {
    public:
        virtual ~window_system() = default;
        virtual void terminate() = 0;
        virtual void update() = 0;


        virtual std::shared_ptr<window_interface> create_window(int width, int height, std::string&& title) = 0;
        virtual void destroy_window(std::shared_ptr<window_interface>) = 0;

        [[nodiscard]] nx::ref<window_interface> get_current_window() const { return current_window_; }
        void virtual set_current_window(const std::shared_ptr<window_interface>& window) { current_window_ = window; }

        std::shared_ptr<nx::event::event_system> events;

    protected:
        std::shared_ptr<window_interface> current_window_;
    };
}
