

#include "opengl_render_api.h"

#include "opengl_render_command.h"
#include "opengl_shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "log/logger.h"

opengl_render_api::~opengl_render_api()
{
}

nx::render::render_backend opengl_render_api::get_api() const
{
    return nx::render::render_backend::opengl;
}



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-function-type"
void opengl_render_api::init()
{
    NX_LOG_TRACE("opengl_render_api::init");
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        NX_LOG_ERROR("Failed to initialize GLAD");
        return;
    }
    
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    
    glDebugMessageCallback(opengl_message_callback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
#pragma clang diagnostic pop


void opengl_render_api::shutdown()
{
    NX_LOG_TRACE("opengl_render_api::shutdown");
}

nx::ref<nx::render::render_command> opengl_render_api::create_render_command()
{
    return nx::create_ref<opengl_render_command>();
}

nx::ref<nx::render::shader> opengl_render_api::create_shader()
{
    return nx::create_ref<opengl_shader>();
}

