#pragma once
#include <string>
#include <vector>

#include "opengl_mesh.h"
#include "opengl_shader.h"
#include "opengl_texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
class model
{
public:
    model(const char* path);
    void draw(opengl_shader& shader) const;
private:
    std::vector<opengl_mesh> meshes_;
    std::string directory_;
    std::vector<opengl_texture> textures_loaded_;
    void load_model(const std::string& path);
    void process_node(aiNode* node, const aiScene* scene);
    opengl_mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::vector<opengl_texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string type_name);
    unsigned int texture_from_file(const char* path, const std::string& directory, bool gamma = false);
};
