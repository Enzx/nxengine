#pragma once
#include <memory>
#include <string>

#include "event/event_system.h"

class window_interface
{
public:
    window_interface() = default;
    window_interface(const window_interface& other) = delete;
    window_interface(window_interface&& other) noexcept = delete;
    window_interface& operator=(const window_interface& other) = delete;
    window_interface& operator=(window_interface&& other) noexcept = delete;

    window_interface(const int width, const int height, std::string& title) : width_(width), height_(height),
                                                                              title_(std::move(title))
    {
        events = std::make_unique<nx::event::event_system>();
        window_id_ = last_window_id_++;
    }

    int get_id() const
    {
        return window_id_;
    }

    virtual ~window_interface() = default;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void close() = 0;

    virtual void update() = 0;
    virtual void* get_raw_pointer() = 0;
    std::unique_ptr<nx::event::event_system> events = nullptr;

protected:
    int width_ = 0;
    int height_ = 0;
    std::string title_;
    int window_id_ = 0;

private:
    inline static int last_window_id_ = 0;
};
