#pragma once
#include "input_action.h"

namespace input
{
    class input_system 
    {
    public:
        virtual void update() = 0;
        virtual void add_input_action(const std::shared_ptr<input_action>& action) = 0;
        virtual void remove_input_action(const std::shared_ptr<input_action>& action) = 0;
        virtual ~input_system() = default;

    protected:
        std::vector<std::shared_ptr<input_action>> actions_{};
    };

    
}
