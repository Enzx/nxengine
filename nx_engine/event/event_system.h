#pragma once
#include <map>
#include <memory>
#include <typeindex>
#include <vector>
#include <any>

#include "handler.h"

namespace event
{
    class handler_base;

    class event_system final
    {
    public:
        template <typename TMessage, typename TAgent>
        void subscribe(void (TAgent::*function)(const TMessage&), TAgent* instance)
        {
            const auto wrapper = new class member_function_wrapper<TAgent, TMessage>(function, instance);
            handlers_[std::type_index(typeid(TMessage))].push_back(std::unique_ptr<handler_base>(wrapper));
        }

        //subscribe static functions
        template <typename TMessage>
        void subscribe(void (*function)(const TMessage&))
        {
            auto wrapper = new class static_function_wrapper<TMessage>(function);
            handlers_[std::type_index(typeid(TMessage))].push_back(std::unique_ptr<handler_base>(wrapper));
        }

        //add overload to subscribe const functions
        template <typename TMessage, typename TAgent>
        void subscribe(void (TAgent::*function)(const TMessage&) const, TAgent* instance)
        {
            const auto wrapper = new class member_function_wrapper<TAgent, TMessage>(function, instance);
            handlers_[std::type_index(typeid(TMessage))].push_back(std::unique_ptr<handler_base>(wrapper));
        }

        //unsubscribe all
        template <typename TMessage>
        void unsubscribe_all()
        {
            handlers_[std::type_index(typeid(TMessage))].clear();
        }

        template <typename TMessage, typename TAgent>
        void unsubscribe(void (TAgent::*function)(const TMessage&), const TAgent* instance)
        {
            auto& handlers = handlers_[std::type_index(typeid(TMessage))];
            const auto it = std::find_if(
                handlers.begin(), handlers.end(),
                [&](const std::unique_ptr<handler_base>& handler)
                {
                    auto wrapper = static_cast<member_function_wrapper<TAgent, TMessage>*>
                        (handler.get());
                    return wrapper->equals(function, instance);
                });
            if (it != handlers.end())
            {
                handlers.erase(it);
            }
        }

        template <typename TMessage>
        void publish(const TMessage& msg)
        {
            const auto type = std::type_index(typeid(TMessage));
            if (const auto it = handlers_.find(type); it != handlers_.end())
            {
                for (const auto& handler : it->second)
                {
                    handler->handle(&msg);
                }
            }
        }

    private:
        std::map<std::type_index, std::vector<std::unique_ptr<handler_base>>> handlers_;
    };
}
