#pragma once
#include <glm/vec2.hpp>

namespace input
{
    class mouse
    {
    public:
        mouse() = default;
        mouse(const mouse& other) = delete;
        mouse(mouse&& other) noexcept = delete;
        mouse& operator=(const mouse& other) = delete;
        mouse& operator=(mouse&& other) noexcept = delete;

        static glm::bvec2 get_screen_position()
        {
            return screen_position_;
        }

        static glm::bvec2 get_scroll_offset()
        {
            return scroll_offset_;
        }

        virtual ~mouse() = default;

    protected:
        friend class input_system;
        static glm::bvec2 screen_position_;
        static glm::bvec2 scroll_offset_;
    };

}
