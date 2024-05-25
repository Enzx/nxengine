#pragma once
#include "render/vertex_array.h"

namespace opengl
{
    class opengl_vertex_array : public render::vertex_array
    {
    public:
        opengl_vertex_array();
        ~opengl_vertex_array() override;
        void bind() const override;
        void unbind() const override;
        void add_vertex_buffer(const std::shared_ptr<render::vertex_buffer>& vertex_buffer) override;
        void set_index_buffer(const std::shared_ptr<render::index_buffer>& index_buffer) override;
        [[nodiscard]] const std::vector<std::shared_ptr<render::vertex_buffer>>& get_vertex_buffers() const override { return vertex_buffers_; }
        [[nodiscard]] const std::shared_ptr<render::index_buffer>& get_index_buffer() const override { return index_buffer_; }
    private:
        uint32_t id_{};
        std::vector<std::shared_ptr<render::vertex_buffer>> vertex_buffers_;
        std::shared_ptr<render::index_buffer> index_buffer_;
    
    };
}