#pragma once
#include <memory>

namespace render
{
    class vertex_buffer
    {
    public:
        virtual ~vertex_buffer() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    class index_buffer
    {
    public:
        virtual ~index_buffer() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    class buffer
    {
    public:
        static vertex_buffer* create_vertex_buffer() ;
        static index_buffer* create_index_buffer() ;
    };
}
