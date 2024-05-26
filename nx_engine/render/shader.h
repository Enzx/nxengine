#pragma once
#include "glm/glm.hpp"

#include "base/nx_pch.h"

class shader
{
public:
    shader(const shader& other) = delete;
    shader(shader&& other) noexcept = delete;
    shader& operator=(const shader& other) = delete;
    shader& operator=(shader&& other) noexcept = delete;
    
    shader() = default;
    virtual ~shader() = default;
    virtual void compile(const std::string& vertex_shader_source, const std::string& fragment_shader_source) = 0;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void set_bool(const std::string& name, bool value) const = 0;
    virtual void set_int(const std::string& name, int value) const = 0;
    virtual void set_float(const std::string& name, float value) const = 0;
    virtual void set_float3(const std::string& name, float v0, float v1, float v2) const = 0;
    virtual void set_float4(const std::string& name, float v0, float v1, float v2, float v3) const = 0;
    virtual void set_mat4(const std::string& name, glm::mat4 mat) const = 0;
    
};
