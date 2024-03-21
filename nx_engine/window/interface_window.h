#pragma once
#include <memory>
#include <string>

#include "../event/event_system.h"

class interface_window
{
public:
    interface_window() = default;
    interface_window(const interface_window& other) = delete;
    interface_window(interface_window&& other) noexcept = delete;
    interface_window& operator=(const interface_window& other) = delete;
    interface_window& operator=(interface_window&& other) noexcept = delete;

    interface_window(const int width, const int height, std::string& title) : width_(width), height_(height), title_(std::move(title))
    {
        events = std::make_unique<event::event_system>();
    }

    virtual ~interface_window() = default;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update() = 0;
    virtual void* get_raw_pointer() = 0;
    std::unique_ptr<event::event_system> events = nullptr;

protected:
    int width_ = 0;
    int height_ = 0;
    std::string title_;
};
