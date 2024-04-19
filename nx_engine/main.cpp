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
#include "render/shader.h"

std::shared_ptr<interface_window> main_window;
bool running = true;

void on_window_close(const window::event::close& event)
{
    if (event.window_id != main_window->get_id())
        return;
    std::cout << "Window closed\n";
    running = false;
}


void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void handle_signal(const int signal)
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
    if (const auto signal_handler = signal(SIGINT, handle_signal); signal_handler == SIG_ERR)
    {
        std::cerr << "Failed to register signal handler\n";
        return -1;
    }

    service::locator services;
    const auto window_system = services.add<window::glfw_window_system>();
    main_window = window_system->create_window(640, 480, "Hello World");
    window_system->set_current_window(main_window);
    main_window->events->subscribe<window::event::close>(&on_window_close);

    const auto input_system = services.add<input::glfw_input>();

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 640, 480);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(main_window->get_raw_pointer()), framebuffer_size_callback);

    const auto action = std::make_shared<input::input_action>(
        input::device_type::keyboard,
        input::key_code::escape,
        "Close_Window");
    input_system->add_input_action(action);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)main_window->get_raw_pointer(), true);
    const auto glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    constexpr float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    }; 
    const unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
      //  1, 2, 3    // second triangle
    }; 

    shader default_shader("assets/shaders/default.vert", "assets/shaders/default.frag");


    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // or GL_LINE to see wireframes or GL_POINT for points
    glPointSize(5.0f);
    
    while (running)
    {
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                         clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float redValue = (cos(timeValue) / 3.0f) + 0.3f;
        float blueValue = (sin(timeValue) / 3.14f) + 0.2f;
        
        default_shader.use();
        default_shader.set_float4("ourColor", redValue, greenValue, blueValue, 1.0f);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        
        input_system->update();


        if (action->get_state() == input::key_state::press)
            main_window->close();

    

        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))
                // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        window_system->update();

    }
    window_system->terminate();
    std::cout << "[[Finished]]\n";
    return 0;
}
