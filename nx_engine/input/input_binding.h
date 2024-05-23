#pragma once
#include "input.h"

namespace input
{
    class input_binding
    {
    public:
        virtual void update() = 0;
        virtual ~input_binding() = default;

        [[nodiscard]] key_state get_state() const
        {
            return target_state_;
        }

        [[nodiscard]] bool triggered() const
        {
            return triggered_;
        }

    protected:
        bool triggered_ = false;
        key_state target_state_ = key_state::none;
        key_state current_state_ = key_state::none;
    };

    class keyboard_binding : public input_binding
    {
    public:
        explicit keyboard_binding(const key_code& key,
                                  const key_modifiers& mods = key_modifiers::none)
            : key(key),
              modifiers(mods)
        {
        }


        key_code key;
        key_modifiers modifiers;
    };

    class mouse_binding : public input_binding
    {
    public:
        explicit mouse_binding(const mouse_button& button, key_modifiers = key_modifiers::none) :
            button(button)
        {
        }

        mouse_button button;
    };
}
