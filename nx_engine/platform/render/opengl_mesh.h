#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "opengl_shader.h"
#include "opengl_texture.h"
#define MAX_BONE_INFLUENCE 4
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int bone_ids_[MAX_BONE_INFLUENCE];
    int m_Weights_[MAX_BONE_INFLUENCE];
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
    std::vector<Texture> textures;

    opengl_mesh() = delete;
    opengl_mesh(const opengl_mesh& other) = delete;
    opengl_mesh(opengl_mesh&& other) noexcept = default;
    opengl_mesh& operator=(const opengl_mesh& other) = delete;
    opengl_mesh& operator=(opengl_mesh&& other) noexcept = delete;
    opengl_mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~opengl_mesh();
    void bind() const;
    void unbind() const;
    void draw(opengl_shader& shader) const;

private:
    unsigned int  vao_{}, vbo_{},  ebo_{}; // vertex array object, vertex buffer object, element buffer object
    void setup_mesh();
};
