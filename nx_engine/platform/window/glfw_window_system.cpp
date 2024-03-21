#include "glfw_window_system.h"
#include "glfw_window.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "window_events.h"

void window::glfw_window_system::initialize()
{
	if (glfwInit() == false)
	{
		//Error
		std::cout << "Failed to initialize the glfw system";
		return;
	}
}

void window::glfw_window_system::terminate()
{
	glfwTerminate();
}

void window::glfw_window_system::update()
{
	glfwPollEvents();

	for (const auto& win : windows_)
	{
		win->update();
	}
}

void window::glfw_window_system::on_window_close(const events::window_close& event)
{
	events->publish(event);
}

std::shared_ptr<interface_window> window::glfw_window_system::create_window(int width, int height, std::string&& title)
{
	std::shared_ptr<interface_window> window = std::make_shared<glfw_window>(width, height, title);
	window->events->subscribe<events::window_close>(&glfw_window_system::on_window_close, this);
	
	
	windows_.push_back(window);
	return window;
}

void window::glfw_window_system::destroy_window(const std::shared_ptr<interface_window> window)
{
	const auto win = static_cast<GLFWwindow*>(window->get_raw_pointer());
	const auto it = std::ranges::find(windows_, window);
	windows_.erase(it);
	glfwDestroyWindow(win);
}


