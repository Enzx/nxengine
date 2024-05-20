#pragma once
#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "detail/has_on_create.h"

namespace service
{
    class locator
    {
    public:
        virtual ~locator() = default;
    };

    /**
     * \brief Service locator class to register and retrieve services by type name
     * \details This class is a singleton and is used to register and retrieve services by type name
     * \note This class is not thread safe
     * \example
     *          service::locator service;
     *          service.add<test_service>();
     *          service.get<test_service>()->test();
     *          service.remove<test_service>();
     */
    template <typename thread_policy>
    class policy_locator : public locator, private thread_policy
    {
    public:
        /**
         * \brief Add a service to the locator
         * \tparam type_name The type of the service to add
         * \tparam Args The types of the arguments to pass to the service constructor
         * \param instance The instances of the services to add
         */
        template <typename type_name, typename... Args>
        std::shared_ptr<type_name> add(Args&&... instance)
        {
            const auto service = std::make_shared<type_name>(std::forward<Args>(instance)...);
            if constexpr (detail::has_on_create<type_name, void(locator*)>::value)
            {
                service->on_create(this);
            }
            const auto type = std::type_index(typeid(type_name));
            this->lock();
            services_[type] = std::move(service);
            this->unlock();
            return std::static_pointer_cast<type_name>(services_[type]);
        }

        /**
         * \brief Get a service from the locator
         * \tparam type_name The type of the service to get
         * \return The instance of the service
         */
        template <typename type_name>
        std::shared_ptr<type_name> get()
        {
            const auto type = std::type_index(typeid(type_name));
            this->lock();
            const auto service = std::static_pointer_cast<type_name>(services_[type]);
            this->unlock();
            return service;
        }

        /**
         * \brief Remove a service from the locator
         * \tparam type_name The type of the service to remove
         */
        template <typename type_name>
        void remove()
        {
            const auto type = std::type_index(typeid(type_name));
            this->lock();
            services_.erase(type);
            this->unlock();
        }

        /**
         * \brief Clear all services from the locator
         */
        void clear()
        {
            this->lock();
            services_.clear();
            this->unlock();
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<void>> services_;
    };
}
