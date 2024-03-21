#pragma once
#include "../../event/event_system.h"

namespace service
{
    /**
     * \brief Interface for a service class to be used with the service locator
     */
    class interface_service
    {
    public:
        interface_service()
        {
            events = std::make_unique<event::event_system>();
        }

        interface_service(const interface_service& other) = delete;
        interface_service(interface_service&& other) noexcept = delete;
        interface_service& operator=(const interface_service& other) = delete;
        interface_service& operator=(interface_service&& other) noexcept = delete;
        virtual ~interface_service() = default;

        std::unique_ptr<event::event_system> events = nullptr;

    private:
        friend class locator;

        virtual void on_create(const locator* locator)
        {
        }
    };
}
