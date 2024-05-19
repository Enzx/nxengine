#pragma once
#include <string>


class opengl_texture 
{
public:
    opengl_texture() = default;
    opengl_texture(const opengl_texture& other) = default;
    opengl_texture(opengl_texture&& other) noexcept = default;
    opengl_texture& operator=(const opengl_texture& other) = default;
    opengl_texture& operator=(opengl_texture&& other) noexcept = default;
    ~opengl_texture();


    void load(const std::string& path);
    void bind() const;
    void unbind() const;

    unsigned int id{};

    std::string path{};
    std::string type;

private:
    int width_{};
    int height_{};
    int channels_{};
 };
