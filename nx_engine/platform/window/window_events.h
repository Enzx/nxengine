#pragma once

namespace window
{
    namespace events
    {
        struct window_resize
        {
            int width;
            int height;
        };
        struct window_move
        {
            int x;
            int y;
        };
        struct window_focus
        {
            
        };
        struct window_lost_focus
        {
            
        };
        struct window_close
        {
            
        };
    }
  
}

