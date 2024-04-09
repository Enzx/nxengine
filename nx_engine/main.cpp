#define GLFW_INCLUDE_NONE

#include <iostream>

#include "data_types/service_locator/locator.h"
#include "event/event_system.h"
#include "platform/window/glfw_window_system.h"
#include "window/window_system.h"
#include "window/interface_window.h"
#include "window/window_events.h"


std::shared_ptr<interface_window> main_window;
bool running = true;

void on_window_close(const window::events::window_close& event)
{
    if (event.window_id != main_window->get_id())
        return;
    std::cout << "Window closed\n";
    running = false;
}


int main()
{
    service::locator services;
    services.add<window::glfw_window_system>();
    const auto window_system = services.get<window::window_system>();
    window_system->initialize();
    main_window = window_system->create_window(640, 480, "Hello World");
    main_window->events->subscribe<window::events::window_close>(&on_window_close);
    event::event_system events;

    while (running)
    {
        window_system->update();
    }
    window_system->terminate();
    return 0;
}
