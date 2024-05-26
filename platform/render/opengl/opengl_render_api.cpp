

#include "opengl_render_api.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "log/logger.h"

opengl_render_api::~opengl_render_api()
{
}

render_backend opengl_render_api::get_api() const
{
    return render_backend::opengl;
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
