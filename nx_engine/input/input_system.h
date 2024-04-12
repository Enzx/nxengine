#pragma once
#include "input_action.h"
#include "../data_types/service_locator/interface_service.h"

namespace input
{
    class input_system : public service::interface_service
    {
    public:
        virtual void update() = 0;
        virtual void add_input_action(const std::shared_ptr<input_action>& action) = 0;
        virtual void remove_input_action(const std::shared_ptr<input_action>& action) = 0;

    protected:
        std::vector<std::shared_ptr<input_action>> actions_{};
    };

    
}
