#pragma once
#include <glm/glm.hpp>

#include "base/base.h"

class renderer
{
public:
    void init();
    void shutdown();
    void begin_scene();
    void end_scene();
    void submit();
private:
    struct scene_data
    {
        glm::mat4 view_projection_matrix;
    };

    nx::scope<scene_data> scene_data_;
};
