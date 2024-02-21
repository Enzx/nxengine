#pragma once
#include <string>

class i_window
{
public:
    i_window() = default;

    i_window(int width, int height, std::string& title) : _width(width), _height(height), _title(title)
    {
    }

    virtual ~i_window() = default;
    virtual void show() = 0;
    virtual void hide() = 0;

private:
    int _width = 0;
    int _height = 0;
    std::string _title;
};
