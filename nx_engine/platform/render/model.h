#pragma once
#include <string>
#include <vector>

#include "opengl_mesh.h"
#include "opengl_shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <filesystem>
class model
{
public:
    explicit model(const std::string& path);
    void draw(opengl_shader& shader) const;
private:
    std::vector<opengl_mesh> meshes_;
    std::filesystem::path directory_;
    std::vector<Texture> textures_loaded_;
    void load_model(const std::string& path);
    void process_node(const aiNode* node, const aiScene* scene);
    opengl_mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string type_name);
    unsigned int texture_from_file(const char* path, const std::string& directory, bool gamma = false);
};
