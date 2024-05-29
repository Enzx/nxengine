#pragma once
#include <glm/glm.hpp>

namespace nx {
    namespace render {

        class camera {
        public:
            camera();

            [[nodiscard]] glm::mat4 get_view_projection_matrix() const;
            [[nodiscard]] glm::mat4 get_projection_matrix() const;
            [[nodiscard]] glm::mat4 get_view_matrix() const;
            [[nodiscard]] glm::vec3 get_position() const;

            void look_at(const glm::vec3& target);
            void set_position(const glm::vec3& position);
    
            void update_projection_matrix();
            void update_projection_matrix(const float& fov, const float& aspect_ratio, const float& near_clip, const float& far_clip);

        private:
            void update_view_matrix();

            glm::vec3 position_ = glm::vec3(0.0f);
            glm::mat4 view_matrix_ = glm::mat4(1.0f);
            glm::mat4 projection_matrix_ = glm::mat4(1.0f);
            glm::mat4 view_projection_matrix_ = glm::mat4(1.0f);

            float fov_ = 45.0f;
            float aspect_ratio_ = 4.0f / 3.0f;
            float near_clip_ = 0.1f;
            float far_clip_ = 100.0f;
            glm::vec3 forward_;
            glm::vec3 right_;
            glm::vec3 up_;
        };

    } // namespace render
} // namespace nx
