#pragma once
#include <glm/fwd.hpp>

class opengl_shader
{
public:
    unsigned int id;
    opengl_shader(const wchar_t* vertex_shader_path, const wchar_t* fragment_shader_path);
    opengl_shader() = default;
    ~opengl_shader();
    void compile(const wchar_t* vertex_shader_source, const wchar_t* fragment_shader_source);
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
    
