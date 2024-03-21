#pragma once

namespace event
{
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

        virtual void handle(const void* msg) = 0;
    };


    template <typename TAgent, typename TMessage>
    class member_function_wrapper final : public handler_base
    {
        typedef void (TAgent::*callback_func)(const TMessage&);
        typedef void (TAgent::*callback_func_const)(const TMessage&) const;

        callback_func m_function_;

        TAgent* m_instance_;

    public:
        //constructor for non-const callback func
        member_function_wrapper(const callback_func callback, TAgent* instance)
            : handler_base(), m_function_(callback), m_instance_(instance)
        {
        }

        //constructor for const callback func
        member_function_wrapper(const callback_func_const callback, const TAgent* instance)
            : handler_base(),
              m_function_(reinterpret_cast<callback_func>(callback)),
              m_instance_(const_cast<TAgent*>(instance))
        {
        }

        member_function_wrapper(const member_function_wrapper& other) = delete;
        member_function_wrapper(member_function_wrapper&& other) noexcept = delete;
        member_function_wrapper& operator=(const member_function_wrapper& other) = delete;
        member_function_wrapper& operator=(member_function_wrapper&& other) noexcept = delete;

        void handle(const void* msg) override
        {
            //call static function
            if (m_instance_ == nullptr)
            {
                m_function_(static_cast<const TMessage*>(msg));
                return;
            }
            
            (m_instance_->*m_function_)(*static_cast<const TMessage*>(msg));
        }

        // Equality check based on instance and member function pointers
        bool equals(callback_func callback, TAgent* instance) const
        {
            return m_instance_ == instance && m_function_ == callback;
        }

        ~member_function_wrapper() override
        {
            m_function_ = nullptr;
            m_instance_ = nullptr;
        }
    };
}
