#pragma once
#include <algorithm>

class message
{
public:
    message() = default;
    message(const message& other) = default;
    message(message&& other) noexcept = default;
    virtual ~message() = default;

    message& operator=(const message& other)
    {
        if (this == &other)
            return *this;
        return *this;
    }

    message& operator=(message&& other) noexcept
    {
        if (this == &other)
            return *this;
        return *this;
    }
};

template <typename message_type>
class message_wrapper final : public message
{
    message_type msg_;
    explicit message_wrapper(message_type&& msg) : msg_(std::move(msg)) {}
};

class handler_base
{
public:
    handler_base() = default;
    handler_base(const handler_base& other) = default;
    handler_base(handler_base&& other) noexcept = default;
    virtual ~handler_base() = default;

    handler_base& operator=(const handler_base& other)
    {
        if (this == &other)
            return *this;
        return *this;
    }

    handler_base& operator=(handler_base&& other) noexcept
    {
        if (this == &other)
            return *this;
        return *this;
    }

    virtual void handle(const message* msg) = 0;
};


template <typename TAgent, typename TMessage>
class member_function_wrapper final : public handler_base
{
    typedef void (TAgent::*callback_func)(const TMessage&);

    callback_func m_function_;

    TAgent* m_instance_;

public:
    member_function_wrapper(const callback_func callback, TAgent* instance)
        : handler_base(), m_function_(callback), m_instance_(instance)
    {
    }

    void handle(const message* msg) override
    {
        if (auto* typed_wrapper = dynamic_cast<message_wrapper<TMessage>*>(msg)) {
            (m_instance_->*m_function_)(typed_wrapper->msg_);
        }
    }

    // Equality check based on instance and member function pointers
    bool equals(callback_func callback, TAgent* instance) const
    {
        return m_instance_ == instance && m_function_ == callback;
    }
};
