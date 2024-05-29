#include "camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


namespace nx
{
    namespace render
    {
        camera::camera()
            : position_(0.0f, 0.0f, 3.0f)
        {
            update_projection_matrix();
            update_view_matrix();
        }

        glm::mat4 camera::get_view_projection_matrix() const
        {
            return view_projection_matrix_;
        }

        glm::mat4 camera::get_projection_matrix() const
        {
            return projection_matrix_;
        }

        glm::mat4 camera::get_view_matrix() const
        {
            return view_matrix_;
        }

        glm::vec3 camera::get_position() const
        {
            return position_;
        }

        void camera::look_at(const glm::vec3& target)
        {
            static constexpr glm::vec3 world_up(0.0f, 1.0f, 0.0f);

            forward_ = normalize(target - position_);
            right_ = normalize(cross(forward_, world_up));
            up_ = normalize(cross(right_, forward_));


            update_view_matrix();
        }

        void camera::set_position(const glm::vec3& position)
        {
            position_ = position;
            update_view_matrix();
        }


        void camera::update_view_matrix()
        {
            view_matrix_ = glm::lookAt(position_, position_ + forward_, up_);

            view_projection_matrix_ = view_matrix_ * projection_matrix_;
        }

        void camera::update_projection_matrix()
        {
            projection_matrix_ = glm::perspective(glm::radians(fov_), aspect_ratio_, near_clip_, far_clip_);
        }

        void camera::update_projection_matrix(const float& fov, const float& aspect_ratio, const float& near_clip,
                                              const float& far_clip)
        {
            fov_ = fov;
            aspect_ratio_ = aspect_ratio;
            near_clip_ = near_clip;
            far_clip_ = far_clip;
            update_projection_matrix();
        }
    } // namespace render
} // namespace nx
