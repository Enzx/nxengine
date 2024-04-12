#include "glfw_input.h"

#include "GLFW/glfw3.h"
#include "../../data_types/service_locator/locator.h"
#include "../window/glfw_window_system.h"

void input::glfw_input::add_input_action(const std::shared_ptr<input_action>& action)
{
    actions_.push_back(action);
}

void input::glfw_input::remove_input_action(const std::shared_ptr<input_action>& action)
{
    std::erase(actions_, action);
}

input::glfw_input::~glfw_input()
{
    actions_.clear();
    window_ = nullptr;
}

void input::glfw_input::on_create(const service::locator*)
{
    window_ = glfwGetCurrentContext();
    assert(window_ != nullptr);
}

void input::glfw_input::update()
{
    for (const auto& action : actions_)
    {
        action->set_state(key_state::none);
        switch (glfwGetKey(window_, static_cast<int>(action->get_key())))
        {
        case GLFW_PRESS:
            action->set_state(key_state::press);
            break;
        case GLFW_RELEASE:
            action->set_state(key_state::release);
            break;
        case GLFW_REPEAT:
            action->set_state(key_state::hold);
            break;
        default:
            break;
        }
    }
}
