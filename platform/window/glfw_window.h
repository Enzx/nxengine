#pragma once
#include "window/interface_window.h"
#include "GLFW/glfw3.h"

namespace window
{
	class glfw_window final : public interface_window
	{
	public:
		glfw_window() = default;
		glfw_window(int width, int height, std::string& title);
		~glfw_window() override;
		glfw_window(const glfw_window& other) = delete;
		glfw_window(glfw_window&& other) noexcept = delete;
		glfw_window& operator=(const glfw_window& other) = delete;
		glfw_window& operator=(glfw_window&& other) noexcept = delete;

		void show() override;
		void hide() override;
		void update() override;
		void* get_raw_pointer() override;
		void close() override;

	private:
		GLFWwindow* window_ = nullptr;

	};
}
