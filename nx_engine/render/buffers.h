#pragma once

#include "log/logger.h"

namespace nx::render
{
    enum class buffer_data_type
    {
        none = 0,
        float1, float2, float3, float4, mat3, mat4, int1, int2, int3, int4, bool1, bool2, bool3, bool4
    };

    class buffer_element
    {
    public:
        static uint32_t buffer_data_type_size(const buffer_data_type type)
        {
            switch (type)
            {
            case buffer_data_type::float1: return 4;
            case buffer_data_type::float2: return 4 * 2;
            case buffer_data_type::float3: return 4 * 3;
            case buffer_data_type::float4: return 4 * 4;
            case buffer_data_type::mat3: return 4 * 3 * 3;
            case buffer_data_type::mat4: return 4 * 4 * 4;
            case buffer_data_type::int1: return 4;
            case buffer_data_type::int2: return 4 * 2;
            case buffer_data_type::int3: return 4 * 3;
            case buffer_data_type::int4: return 4 * 4;
            case buffer_data_type::bool1: return 1;
            case buffer_data_type::bool2: return 1 * 2;
            case buffer_data_type::bool3: return 1 * 3;
            case buffer_data_type::bool4: return 1 * 4;
            case buffer_data_type::none: NX_LOG_ERROR("NONE buffer data type: none");
                break;
            }
            return 0;
        }
        
        buffer_element() = default;

        buffer_element(const buffer_data_type& type, const std::string& name, const bool normalized = false)
            : type_(type), name_(name), size_(buffer_data_type_size(type)), offset_(0), normalized_(normalized)
        {
        }

        [[nodiscard]] buffer_data_type get_type() const { return type_; }
        [[nodiscard]] uint32_t get_size() const { return size_; }
        [[nodiscard]] uint32_t get_offset() const { return offset_; }
        [[nodiscard]] bool get_normalized() const { return normalized_; }

        void set_offset(const uint32_t offset) { offset_ = offset; }

        [[nodiscard]] int get_component_count() const
        {
            switch (type_)
            {
            case buffer_data_type::float1: return 1;
            case buffer_data_type::float2: return 2;
            case buffer_data_type::float3: return 3;
            case buffer_data_type::float4: return 4;
            case buffer_data_type::mat3: return 3 * 3;
            case buffer_data_type::mat4: return 4 * 4;
            case buffer_data_type::int1: return 1;
            case buffer_data_type::int2: return 2;
            case buffer_data_type::int3: return 3;
            case buffer_data_type::int4: return 4;
            case buffer_data_type::bool1: return 1;
            case buffer_data_type::bool2: return 2;
            case buffer_data_type::bool3: return 3;
            case buffer_data_type::bool4: return 4;
            case buffer_data_type::none: NX_LOG_ERROR("NONE buffer data type: none");
                break;
            }
            return 0;
        }

    private:
        buffer_data_type type_;
        std::string name_;
        uint32_t size_;
        uint32_t offset_;
        bool normalized_;
    };

    class buffer_layout
    {
    public:

        buffer_layout(const std::initializer_list<buffer_element>& elements)
            : elements_(elements)
        {
            calculate_offset_and_stride();
        }

        [[nodiscard]] const std::vector<buffer_element>& get_elements() const { return elements_; }
        [[nodiscard]] uint32_t get_stride() const { return stride_; }

        std::vector<buffer_element>::iterator begin() { return elements_.begin(); }
        std::vector<buffer_element>::iterator end() { return elements_.end(); }
        std::vector<buffer_element>::const_iterator begin() const { return elements_.begin(); }
        std::vector<buffer_element>::const_iterator end() const { return elements_.end(); }

    private:
        void calculate_offset_and_stride()
        {
            uint32_t offset = 0;
            stride_ = 0;
            for (auto& element : elements_)
            {
                element.set_offset(offset);
                offset += element.get_size();
                stride_ += element.get_size();
            }
        }

        std::vector<buffer_element> elements_;
        uint32_t stride_{};
    };

    class vertex_buffer
    {
    public:
        vertex_buffer() = default;
        virtual ~vertex_buffer() = default;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual void set_layout(const buffer_layout& layout) = 0;
        virtual const buffer_layout& get_layout() const = 0;
        
    };

    class index_buffer
    {
    public:
        index_buffer() = default;
        virtual ~index_buffer() = default;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual uint32_t get_count() const = 0;
        virtual void set_layout(const buffer_layout& layout) = 0;
        virtual const buffer_layout& get_layout() const = 0;
    };

    class buffer
    {
    public:
        static vertex_buffer* create_vertex_buffer();
        static index_buffer* create_index_buffer();
    };
}
