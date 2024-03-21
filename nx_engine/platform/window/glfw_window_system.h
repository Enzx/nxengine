#pragma once
#include "../../window/window_system.h"
#include <vector>

namespace window
{
	namespace events
	{
		struct window_close;
	}

	class glfw_window_system : public window::window_system
	{
	public:
		//constructor
		glfw_window_system() = default;
		//destructor
		~glfw_window_system() override = default;

		void initialize() override;
		void terminate() override;
		void update() override;
		void on_window_close(const events::window_close& event);
		std::shared_ptr<interface_window> create_window(int width, int height, std::string&& title) override;
		void destroy_window(std::shared_ptr<interface_window>) override;

	private:
		std::vector<std::shared_ptr< interface_window>> windows_;
	};
}
