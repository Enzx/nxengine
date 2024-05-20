#include "opengl_shader.h"
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../log/logger.h"

opengl_shader::opengl_shader(const wchar_t* vertex_shader_path, const wchar_t* fragment_shader_path)
{
    compile(vertex_shader_path, fragment_shader_path);
}

opengl_shader::~opengl_shader()
{
    LOG_DEBUGF("Deleting shader program {}", id);
    glDeleteProgram(id);
}

void opengl_shader::compile(const wchar_t* vertex_shader_source, const wchar_t* fragment_shader_source)
{
    std::string vertex_shader_code;
    std::string fragment_shader_code;
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertex_shader_file.open(vertex_shader_source);
        fragment_shader_file.open(fragment_shader_source);
        std::stringstream vertex_shader_stream, fragment_shader_stream;
        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();
        vertex_shader_file.close();
        fragment_shader_file.close();
        vertex_shader_code = vertex_shader_stream.str();
        fragment_shader_code = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << '\n'
            << e.what() << '\n';
    }

    const char* vertex_shader_code_c = vertex_shader_code.c_str();
    const char* fragment_shader_code_c = fragment_shader_code.c_str();

    //compile shaders
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_code_c, nullptr);
    glCompileShader(vertex_shader);
    check_compile_status(vertex_shader, "VERTEX");

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code_c, nullptr);
    glCompileShader(fragment_shader);
    check_compile_status(fragment_shader, "FRAGMENT");


    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);
    check_link_status(id);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void opengl_shader::use() const
{
    glUseProgram(id);
}

void opengl_shader::set_bool(const char* name, const bool value) const
{
    glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
}

void opengl_shader::set_int(const char* name, const int value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
    GLenum error = glGetError();
    if (error == GL_INVALID_OPERATION)
    {
        LOG_ERRORF("OpenGL Error: {}", error);
    }
}

void opengl_shader::set_float(const char* name, const float value) const
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void opengl_shader::set_float3(const char* name, float v0, float v1, float v2) const
{
    glUniform3f(glGetUniformLocation(id, name), v0, v1, v2);
}

void opengl_shader::set_float4(const char* name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(glGetUniformLocation(id, name), v0, v1, v2, v3);
}

void opengl_shader::set_mat4(const char* name, glm::mat4 mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}

void opengl_shader::check_compile_status(const unsigned int shader, const char* type)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        LOG_ERRORF("ERROR::SHADER::{}::COMPILATION_FAILED\n{}", type, info_log);
    }
    else
    {
        LOG_INFOF("Shader {} compiled successfully", type);
    }
}

void opengl_shader::check_link_status(const unsigned int program) const
{
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        LOG_ERRORF("ERROR::SHADER::PROGRAM::LINK_FAILED\n{}", info_log);
    }
    else
    {
        LOG_INFOF("Shader program ({}) linked successfully", program);
    }
}
