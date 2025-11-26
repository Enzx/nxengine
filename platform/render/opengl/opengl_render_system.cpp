#include "opengl_render_system.h"

#include <filesystem>
#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "opengl_shader.h"
#include "log/logger.h"
#include "GLFW/glfw3.h"
#include "render/camera.h"
#include "window/glfw_window_system.h"


namespace service::policy
{
    class thread_safe;
}

void opengl_render_system::on_create(nx::service::locator<>* locator)
{
    

    // camera


    // draw wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void opengl_render_system::on_window_resize(const window::events::resize& event)
{
    command_.set_viewport(0, 0, event.width, event.height);
}

void opengl_render_system::update()
{
    

    GLenum error = glGetError();
    if (error == GL_INVALID_OPERATION)
    {
        NX_LOG_ERRORF("OpenGL Error: {}", error);
    }
}


opengl_render_system::opengl_render_system()
{
    our_model = nullptr;
}

opengl_render_system::~opengl_render_system()
{
    delete our_model;
}
