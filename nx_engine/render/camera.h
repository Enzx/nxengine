#pragma once
#include <glm/glm.hpp>

class camera
{
public:
    [[nodiscard]] glm::mat4 get_projection_matrix() const;
};
