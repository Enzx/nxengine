#pragma once
#include <string>

#include "../event/event_system.h"


namespace input
{
    // Copied from GLFW3
    enum class key_code
    {
        /* Printable keys */
        space = 32,
        apostrophe = 39,
        /* ' */
        comma = 44,
        /* , */
        minus = 45,
        /* - */
        period = 46, 
        /* . */
        slash = 47,
        /* / */
        alpha_0 = 48,
        alpha_1 = 49,
        alpha_2 = 50,
        alpha_3 = 51,
        alpha_4 = 52,
        alpha_5 = 53,
        alpha_6 = 54,
        alpha_7 = 55,
        alpha_8 = 56,
        alpha_9 = 57,
        semicolon = 59,
        /* ; */
        equal = 61,
        /* = */
        a = 65,
        b = 66,
        c = 67,
        d = 68,
        e = 69,
        f = 70,
        g = 71,
        h = 72,
        i = 73,
        j = 74,
        k = 75,
        l = 76,
        m = 77,
        n = 78,
        o = 79,
        p = 80,
        q = 81,
        r = 82,
        s = 83,
        t = 84,
        u = 85,
        v = 86,
        w = 87,
        x = 88,
        y = 89,
        z = 90,
        left_bracket = 91,
        /* [ */
        backslash = 92,
        /* \ */
        right_bracket = 93,
        /* ] */
        grave_accent = 96,
        /* ` */
        world_1 = 161,
        /* non-US #1 */
        world_2 = 162,
        /* non-US #2 */

        /* Function keys */
        escape = 256,
        enter = 257,
        tab = 258,
        backspace = 259,
        insert = 260,
        delete_ = 261,
        right = 262,
        left = 263,
        down = 264,
        up = 265,
        page_up = 266,
        page_down = 267,
        home = 268,
        end = 269,
        caps_lock = 280,
        scroll_lock = 281,
        num_lock = 282,
        print_screen = 283,
        pause = 284,
        f1 = 290,
        f2 = 291,
        f3 = 292,
        f4 = 293,
        f5 = 294,
        f6 = 295,
        f7 = 296,
        f8 = 297,
        f9 = 298,
        f10 = 299,
        f11 = 300,
        f12 = 301,
        f13 = 302,
        f14 = 303,
        f15 = 304,
        f16 = 305,
        f17 = 306,
        f18 = 307,
        f19 = 308,
        f20 = 309,
        f21 = 310,
        f22 = 311,
        f23 = 312,
        f24 = 313,
        f25 = 314,
        kp_0 = 320,
        kp_1 = 321,
        kp_2 = 322,
        kp_3 = 323,
        kp_4 = 324,
        kp_5 = 325,
        kp_6 = 326,
        kp_7 = 327,
        kp_8 = 328,
        kp_9 = 329,
        kp_decimal = 330,
        kp_divide = 331,
        kp_multiply = 332,
        kp_subtract = 333,
        kp_add = 334,
        kp_enter = 335,
        kp_equal = 336,
        left_shift = 340,
        left_control = 341,
        left_alt = 342,
        left_super = 343,
        right_shift = 344,
        right_control = 345,
        right_alt = 346,
        right_super = 347,
        menu = 348,
    };

    enum class key_state
    {
        none,
        press,
        release,
        hold,
        trigger
    };

    enum class device_type
    {
        keyboard,
        mouse,
        gamepad
    };

    enum class key_modifiers
    {
        none = 0x0000,
        shift = 0x0001,
        control = 0x0002,
        alt = 0x0004,
        super = 0x0008
    };

    struct state_changed
    {
        key_state old_state;
        key_state state;
    };


    class input_action
    {
    public:
        input_action(const device_type device, const key_code key, std::string name) :
            events(std::make_unique<event::event_system>()),
            device_(device),
            state_(key_state::none),
            modifiers_(key_modifiers::none),
            name_(std::move(name)),
            key_(key)
        {
        }
        ~input_action()
        {
            events->unsubscribe_all();
            
        }

        input_action(const input_action& other) = delete;
        input_action(input_action&& other) noexcept = default;
        input_action& operator=(const input_action& other) = delete;
        input_action& operator=(input_action&& other) noexcept = default;
        


        std::unique_ptr<event::event_system> events = nullptr;

        [[nodiscard]] device_type get_device() const
        {
            return device_;
        }

        void set_state(const key_state new_state)
        {
            if (state_ == new_state)
            {
                return;
            }
            events->publish(state_changed{state_, new_state});
            state_ = new_state;
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

        [[nodiscard]] key_code get_key() const
        {
            return key_;
        }

        [[nodiscard]] std::string get_name() const
        {
            return name_;
        }

    private:
        device_type device_;
        key_state state_;
        key_modifiers modifiers_;
        std::string name_;
        key_code key_;
    };
}
