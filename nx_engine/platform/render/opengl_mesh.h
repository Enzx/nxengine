#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "opengl_shader.h"
#include "opengl_texture.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class opengl_mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<opengl_texture> textures;

    opengl_mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<opengl_texture> textures);
    ~opengl_mesh();
    void bind() const;
    void unbind() const;
    void draw(opengl_shader& shader) const;

private:
    unsigned int  vao_{}, vbo_{},  ebo_{}; // vertex array object, vertex buffer object, element buffer object
    void setup_mesh();
};
