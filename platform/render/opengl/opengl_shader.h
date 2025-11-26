#pragma once
#include <glm/fwd.hpp>

#include "render/shader.h"

class opengl_shader : public nx::render::shader
{
public:
    unsigned int id;
    opengl_shader() = default;
    ~opengl_shader() override;
    void compile(const std::string& vertex_shader_source, const std::string& fragment_shader_source) override;
    void bind() const override;
    void unbind() const override;
    void set_bool(const std::string& name, bool value) const override;
    void set_int(const std::string& name, int value) const override;
    void set_float(const std::string& name, float value) const override;
    void set_float3(const std::string& name, float v0, float v1, float v2) const override;
    void set_float4(const std::string& name, float v0, float v1, float v2, float v3) const override;
    void set_mat4(const std::string& name, glm::mat4 mat) const override;
private:
    static void check_compile_status(const unsigned int shader, const char* type);
    void check_link_status(const unsigned int program) const;

};
    
