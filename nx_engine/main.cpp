#define GLFW_INCLUDE_NONE

#include <csignal>
#include <iostream>
#include <filesystem>

#include "imgui.h"
#include "data_types/service_locator/locator.h"
#include "event/event_system.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "platform/window/glfw_window_system.h"
#include "window/interface_window.h"
#include "window/window_events.h"
#include "platform/input/glfw_input.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "data_types/service_locator/policy/thread_policy.h"

std::shared_ptr<interface_window> main_window;
bool running = true;

void on_window_close(const window::events::close& event)
{
    if (event.window_id != main_window->get_id()) return;
    std::cout << "Window closed\n";
    running = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void handle_signal(int signal)
{
    if (signal == SIGINT)
        std::cout << "[SIGINT] application terminated signal\n";
    running = false;
}

int main()
{
    const std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << "Current Working Directory: " << cwd << '\n';
    const std::filesystem::path assets_path = cwd / "assets";

    std::cout << "[[Started]]\n";
    if (signal(SIGINT, handle_signal) == SIG_ERR)
    {
        std::cerr << "Failed to register signal handler\n";
        return -1;
    }

    service::policy_locator<service::policy::thread_safe> services;
    auto window_system = services.add<window::glfw_window_system>();
    main_window = window_system->create_window(640, 480, "Hello World");
    window_system->set_current_window(main_window);
    main_window->events->subscribe<window::events::close>(&on_window_close);

    auto input_system = services.add<platform::input::glfw_input>();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }


    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(main_window->get_raw_pointer()), framebuffer_size_callback);

    auto close_input_action = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::escape, "Close_Window");
    auto right_input_action = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::d, "Move_Right");
    auto left_input_action = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::a, "Move_Left");
    auto rotate_right_input_action = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::e, "Rotate_Right");
    auto rotate_left_input_action = std::make_shared<input::input_action>(input::device_type::keyboard, input::key_code::q, "Rotate_Left");

    input_system->add_input_action(close_input_action);
    input_system->add_input_action(right_input_action);
    input_system->add_input_action(left_input_action);
    input_system->add_input_action(rotate_right_input_action);
    input_system->add_input_action(rotate_left_input_action);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)main_window->get_raw_pointer(), true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;



    while (running)
    {
        input_system->update();

        // render

       

        if (close_input_action->get_state() == input::key_state::press)
            main_window->close();
        window_system->update();

        if (glGetError() == GL_INVALID_OPERATION)
        {
            std::cout << "GL_INVALID_OPERATION\n";
        }
    }

    window_system->terminate();

    std::cout << "[[Finished]]\n";
    return 0;
}
