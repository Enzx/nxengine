#pragma once
#include <string>
#include <vector>


class opengl_texture
{
public:
    static std::vector<std::string> our_loaded_textures;

    opengl_texture() = default;
    opengl_texture(const opengl_texture& other) = default;
    opengl_texture(opengl_texture&& other) noexcept = default;
    opengl_texture& operator=(const opengl_texture& other) = default;
    opengl_texture& operator=(opengl_texture&& other) noexcept = default;
    ~opengl_texture();


    void load(const std::string& pth);
    void bind() const;
    void unbind() const;

    unsigned int id{};

    std::string path{};
    std::string type;

private:
    int width_{};
    int height_{};
    int channels_{};
    //add a static vector to store all loaded textures
};
