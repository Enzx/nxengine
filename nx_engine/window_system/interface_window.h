#pragma once
#include <string>

class interface_window
{
public:
    interface_window() = default;

    interface_window(int width, int height, std::string& title) : _width(width), _height(height), _title(title)
    {
    }

    virtual ~interface_window() = default;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update() = 0;
    virtual void* get_raw_pointer() = 0;

private:
    int _width = 0;
    int _height = 0;
    std::string _title;
};
