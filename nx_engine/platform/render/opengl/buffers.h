#pragma once
#include "render/buffers.h"
namespace opengl
{
    class vertex_buffer : public render::vertex_buffer
    {
    public: 
        vertex_buffer(float* vertices, uint32_t size);
        ~vertex_buffer() override;
        void bind() const override;
        void unbind() const override;
    private:
        uint32_t id_{};
    };

    class index_buffer : public render::index_buffer
    {
    public:
        index_buffer(uint32_t* indices, uint32_t count);
        ~index_buffer() override;
        void bind() const override;
        void unbind() const override;
        [[nodiscard]] uint32_t get_count() const override { return count_; }
    private:
        uint32_t id_{};
        uint32_t count_;
    };
}