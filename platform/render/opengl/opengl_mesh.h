#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "buffers.h"
#include "opengl_shader.h"
#include "opengl_vertex_array.h"
#define MAX_BONE_INFLUENCE 4

struct vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int bone_ids[MAX_BONE_INFLUENCE];
    int m_weights[MAX_BONE_INFLUENCE];
};

struct texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class opengl_mesh
{
public:
    std::vector<vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<texture> textures;

    opengl_mesh() = delete;
    opengl_mesh(const opengl_mesh& other) = delete;
    opengl_mesh(opengl_mesh&& other) noexcept = default;
    opengl_mesh& operator=(const opengl_mesh& other) = delete;
    opengl_mesh& operator=(opengl_mesh&& other) noexcept = delete;
    opengl_mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures);
    ~opengl_mesh();
    void bind() const;
    void unbind() const;
    void draw(opengl_shader& shader) const;

private:
std::shared_ptr<opengl::opengl_vertex_array> vertex_array_;
    std::shared_ptr<opengl::vertex_buffer> vertex_buffer_;
    std::shared_ptr<opengl::index_buffer> index_buffer_;
    void setup_mesh();
};
