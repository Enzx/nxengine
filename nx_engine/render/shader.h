#pragma once
#include <glm/fwd.hpp>

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
    void set_mat4(const char* name, glm::mat4 mat) const;
private:
    static void check_compile_status(const unsigned int shader, const char* type);
    void check_link_status(const unsigned int program) const;
};
    
