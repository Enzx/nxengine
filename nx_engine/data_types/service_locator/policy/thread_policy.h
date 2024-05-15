#pragma once
#include <mutex>

namespace service::policy
{
    struct thread_safe
    {
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

    struct not_thread_safe
    {
        void lock() {}
        void unlock() {}
    };
}
