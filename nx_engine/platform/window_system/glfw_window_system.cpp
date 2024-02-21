#include "glfw_window_system.h"
#include "glfw_window.h"
#include "GLFW/glfw3.h"
#include <iostream>

void glfw_window_system::initialize()
{
	if (glfwInit() == false)
	{
		//Error
		std::cout << "Failed to initialize the glfw system";
		return;
	}
}

void glfw_window_system::terminate()
{
	glfwTerminate();
}

void glfw_window_system::update()
{
	glfwPollEvents();

	for (auto win : windows_)
	{
		win->update();
	}
}

std::shared_ptr<interface_window> glfw_window_system::create_window(int width, int height, std::string& title)
{
	std::shared_ptr<interface_window> windowPointer = std::make_shared<glfw_window>(width, height, title);
	windows_.push_back(windowPointer);
	return windowPointer;
}

void glfw_window_system::destroy_window(std::shared_ptr<interface_window> window)
{
	GLFWwindow* win = reinterpret_cast<GLFWwindow*>(window->get_raw_pointer());
	auto it = std::find(windows_.begin(), windows_.end(), window);
	windows_.erase(it);
	glfwDestroyWindow(win);
}


