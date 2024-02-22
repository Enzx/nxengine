#pragma once
#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace service
{
	class interface_service;

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
	class locator
	{
	public:
		/**
		 * \brief Add a service to the locator
		 * \tparam TypeName The type of the service to add
		 * \tparam Args The types of the arguments to pass to the service constructor
		 * \param instance The instances of the services to add
		 */
		template <typename type_name, typename... Args>
		void add(Args&&... instance)
		{
			static_assert(std::is_base_of_v<interface_service, type_name>,
				"ServiceType must be a derived class of interface_service");

			const auto service = std::make_shared<type_name>(std::forward<Args>(instance)...);
			const auto type = std::type_index(typeid(type_name));
			services_[type] = std::move(service);
		}

		/**
		 * \brief Get a service from the locator
		 * \tparam type_name The type of the service to get
		 * \return The instance of the service
		 */
		template <typename type_name>
		std::shared_ptr<type_name> get()
		{
			static_assert(std::is_base_of_v<interface_service, type_name>,
				"ServiceType must be a derived class of interface_service");
			const auto type = std::type_index(typeid(type_name));
			const auto it = services_.find(type);
			for (const auto& servicePair : services_) {
				if (type == servicePair.first ||
					dynamic_cast<type_name*>(servicePair.second.get()) != nullptr)
				{
					return std::static_pointer_cast<type_name>(servicePair.second);
				}
			}

			assert(it != services_.end(), "Service not registered");
			return std::static_pointer_cast<type_name>(services_[typeid(type_name)]);
		}

		/**
		 * \brief Remove a service from the locator
		 * \tparam type_name The type of the service to remove
		 */
		template <typename type_name>
		void remove()
		{
			const auto type = std::type_index(typeid(type_name));
			auto it = services_.find(type);
			assert(it != services_.end(), "Service not registered");

			services_.erase(it);
		}

		/**
		 * \brief Clear all services from the locator
		 */
		void clear()
		{
			services_.clear();
		}

	private:
		std::unordered_map<std::type_index, std::shared_ptr<interface_service>> services_;
	};
}
