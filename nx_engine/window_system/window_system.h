#pragma once
#include <memory>
#include <string>

class i_window;

namespace window_system
{
    class window_system
    {
    public:
        virtual ~window_system() = default;
        virtual void initialize() = 0;
        virtual void terminate() = 0;
        virtual std::shared_ptr<i_window> create_window(int width, int height, std::string& title) = 0;
        virtual void destroy_window() = 0;
    };
}
