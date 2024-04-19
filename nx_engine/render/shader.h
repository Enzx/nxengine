#pragma once
#include <glad/glad.h>

class shader
{
public:
    unsigned int id;
    shader(const char* vertex_shader_path, const char* fragment_shader_path);
    void use() const;
    void set_bool(const char* name, bool value) const;
    void set_int(const char* name, int value) const;
    void set_float(const char* name, float value) const;
    void set_float3(const char* name, float v0, float v1, float v2) const;
    void set_float4(const char* name, float v0, float v1, float v2, float v3) const;
};
