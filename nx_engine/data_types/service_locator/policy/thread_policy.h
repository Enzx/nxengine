#pragma once
#include <mutex>

namespace nx::service::policy
{
    class thread_safe
    {
    public:
        void lock()
        {
            mutex_.lock();
        }

        void unlock()
        {
            mutex_.unlock();
        }

    private:
        std::mutex mutex_;
    };

    class not_thread_safe
    {
    public:
        static void lock() {}
        static void unlock() {}
    };
}
