#pragma once

namespace window
{
    namespace events
    {
        struct window_resize
        {
            int window_id;
            int width;
            int height;
        };
        struct window_move
        {
            int window_id;
            int x;
            int y;
        };
        struct window_focus
        {
            int window_id;

        };
        struct window_lost_focus
        {
            int window_id;

        };
        struct window_close
        {
            explicit window_close(const int id) {  window_id = id;}
            int window_id;
        };
    }
  
}

