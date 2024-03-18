#pragma once
#include <memory>
#include <string>
#include "..\data_types\service_locator\interface_service.h"

class interface_window;
namespace window_system
{
    class window_system : public service::interface_service
    {
    public:
        virtual ~window_system() = default;
        virtual void initialize() = 0;
        virtual void terminate() = 0;
        virtual void update() = 0;

        virtual std::shared_ptr<interface_window> create_window(int width, int height, std::string&& title) = 0;
        virtual void destroy_window(std::shared_ptr<interface_window>) = 0;
    };
}
