#pragma once
#include <cstdio>

#include "glad/glad.h"
#include "render/render_api.h"

class opengl_render_api final : public render_api
{
public:
    opengl_render_api() = default;
    ~opengl_render_api() override;
    [[nodiscard]] render_backend get_api() const override;
    void init() override;
    void shutdown() override;

    static void APIENTRY opengl_message_callback(GLenum source,
                                                 const GLenum type,
                                                 GLuint id,
                                                 const GLenum severity,
                                                 GLsizei length,
                                                 const GLchar* message,
                                                 const void* userParam)
    {
        int _ = fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "",
                type, severity, message);
    }
};
