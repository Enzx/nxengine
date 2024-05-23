#pragma once
#include <string>
#include "input.h"
#include "input_binding.h"
#include "../event/event_system.h"


namespace input
{
    class input_action
    {
    public:
        input_action(input_binding* const device, std::string name) :
            events(std::make_unique<event::event_system>()),
            binding_(device),
            state_(key_state::none),
            modifiers_(key_modifiers::none),
            name_(std::move(name))
        {
        }

        ~input_action() = default;

        input_action(const input_action& other) = delete;
        input_action(input_action&& other) noexcept = default;
        input_action& operator=(const input_action& other) = delete;
        input_action& operator=(input_action&& other) noexcept = default;


        void update()
        {
            binding_->update();
            set_state(binding_->get_state());
        }

        [[nodiscard]] key_state get_state() const
        {
            return state_;
        }

        [[nodiscard]] key_modifiers get_modifiers() const
        {
            return modifiers_;
        }

        void set_modifiers(const key_modifiers modifiers)
        {
            modifiers_ = modifiers;
        }

        [[nodiscard]] std::string get_name() const
        {
            return name_;
        }

        std::unique_ptr<event::event_system> events = nullptr;

    private:
        void set_state(const key_state new_state)
        {
            if (state_ == new_state)
            {
                return;
            }
            events->publish(state_changed{state_, new_state});
            state_ = new_state;
        }

        input_binding* binding_;
        key_state state_;
        key_modifiers modifiers_;
        std::string name_;
    };
}
