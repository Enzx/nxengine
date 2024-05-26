#pragma once
#include "render/buffers.h"

namespace opengl
{
    class vertex_buffer : public nx::render::vertex_buffer
    {
    public:
        vertex_buffer(float* vertices, uint32_t size);
        ~vertex_buffer() override;
        void bind() const override;
        void unbind() const override;
        void set_layout(const nx::render::buffer_layout& layout) override;
        const nx::render::buffer_layout& get_layout() const override;

    private:
        uint32_t id_{};
        nx::render::buffer_layout layout_{};
    };

    class index_buffer : public nx::render::index_buffer
    {
    public:
        index_buffer(uint32_t* indices, uint32_t count);
        ~index_buffer() override;
        void bind() const override;
        void unbind() const override;
        [[nodiscard]] uint32_t get_count() const override { return count_; }
        void set_layout(const nx::render::buffer_layout& layout) override;
        [[nodiscard]] const nx::render::buffer_layout& get_layout() const override;

    private:
        uint32_t id_{};
        uint32_t count_{};
        nx::render::buffer_layout layout_{};
    };
}
