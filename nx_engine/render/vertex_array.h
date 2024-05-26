#pragma once
#include "buffers.h"

namespace nx::render
{
    class vertex_array
    {
    public:
        vertex_array(const vertex_array& other) = delete;
        vertex_array(vertex_array&& other) noexcept = delete;
        vertex_array& operator=(const vertex_array& other) = delete;
        vertex_array& operator=(vertex_array&& other) noexcept = delete;

        vertex_array() = default;
        virtual ~vertex_array() = default;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        void virtual add_vertex_buffer(const std::shared_ptr<vertex_buffer>& vertex_buffer) = 0;
        void virtual set_index_buffer(const std::shared_ptr<index_buffer>& index_buffer) = 0;
        [[nodiscard]] virtual const std::vector<std::shared_ptr<vertex_buffer>>& get_vertex_buffers() const = 0;
        [[nodiscard]] virtual const std::shared_ptr<index_buffer>& get_index_buffer() const = 0;
        
    };
}