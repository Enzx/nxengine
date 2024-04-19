#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

shader::shader(const char* vertex_shader_path, const char* fragment_shader_path)
{
    std::string vertex_shader_code;
    std::string fragment_shader_code;
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertex_shader_file.open( vertex_shader_path);
        fragment_shader_file.open(fragment_shader_path);
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

    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << '\n';
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code_c, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << '\n';
    }

    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void shader::use() const
{
    glUseProgram(id);
}

void shader::set_bool(const char* name, const bool value) const
{
    glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
}

void shader::set_int(const char* name, const int value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void shader::set_float(const char* name, const float value) const
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void shader::set_float3(const char* name, float v0, float v1, float v2) const
{
    glUniform3f(glGetUniformLocation(id, name), v0, v1, v2);
}

void shader::set_float4(const char* name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(glGetUniformLocation(id, name), v0, v1, v2, v3);
}


