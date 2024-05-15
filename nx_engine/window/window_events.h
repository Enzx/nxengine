#pragma once

namespace window::events
{
    struct resize
    {
        int window_id;
        int width;
        int height;
    };
    struct move
    {
        int window_id;
        int x;
        int y;
    };
    struct focus
    {
        int window_id;

    };
    struct focus_lost
    {
        int window_id;

    };
    struct close
    {
        explicit close(const int id) {  window_id = id;}
        int window_id;
    };
}

