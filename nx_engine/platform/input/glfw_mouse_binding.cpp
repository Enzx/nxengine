#include "glfw_mouse_binding.h"

#include "GLFW/glfw3.h"

void glfw_mouse_binding::update()
{
    triggered_ = false;
    current_state_ = input::key_state::none;
     if( glfwGetMouseButton(window_, static_cast<int>(button)) == GLFW_PRESS )
     {
         current_state_ = input::key_state::press;
     }
     if( glfwGetMouseButton(window_, static_cast<int>(button)) == GLFW_RELEASE )
     {
         current_state_ = input::key_state::release;
     }
      if(current_state_ == target_state_)
      {
          triggered_ = true;
      }
}

glfw_mouse_binding::~glfw_mouse_binding()
{
    window_ = nullptr;
}
