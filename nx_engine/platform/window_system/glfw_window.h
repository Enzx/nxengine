#pragma once
#include "../../window_system/interface_window.h"
#include "GLFW/glfw3.h"

class glfw_window : public interface_window
{
public:
	glfw_window() = default;
	glfw_window(int width, int height, std::string& title);
	~glfw_window() override;

	void show() override;
	void hide() override;
	void update() override;
	void* get_raw_pointer() override;

private:
	GLFWwindow* window_ = nullptr;

};
