#pragma once
#include "input_action.h"
#include "mouse.h"

namespace nx::input
{
    class input_system 
    {
    public:
        input_system() = default;
        input_system(const input_system& other) = delete;
        input_system(input_system&& other) noexcept = delete;
        input_system& operator=(const input_system& other) = delete;
        input_system& operator=(input_system&& other) noexcept = delete;

        
        void update() const
        {
            for (const auto& action : actions_)
            {
                action->update();
            }
        }
        
         void add_input_action(const std::shared_ptr<input_action>& action)
        {
            actions_.push_back(action);
        }

        
        void remove_input_action(const std::shared_ptr<input_action>& action)
        {
            std::erase(actions_, action);
        
        }
        virtual ~input_system()
        {
            actions_.clear();
        }

    protected:
        std::vector<std::shared_ptr<input_action>> actions_{};

        static void set_mouse_screen_position(const glm::bvec2& position)
        {
            mouse::screen_position_ = position;
        }
    };

    
}
