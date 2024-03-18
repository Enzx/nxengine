#pragma once
#include <map>
#include <memory>
#include <typeindex>
#include <vector>

#include "handler.h"

class handler_base;

class events
{
    std::map<std::type_index, std::vector<std::unique_ptr<handler_base>>> handlers_;

public:
    //subscribe to an event
    template <typename TMessage, typename TAgent>
    void subscribe(void (TAgent::*function)(const TMessage&), TAgent* instance)
    {
        auto wrapper = new class member_function_wrapper<TAgent, TMessage>(function, instance);
        handlers_[std::type_index(typeid(TMessage))].push_back(std::unique_ptr<handler_base>(wrapper));
    }

    //unsubscribe from an event
    template <typename TMessage, typename TAgent>
    void unsubscribe(void (TAgent::*function)(const TMessage&), TAgent* instance)
    {
        auto& handlers = handlers_[std::type_index(typeid(TMessage))];
        auto it = std::find_if(
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

    //publish an event
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
};
