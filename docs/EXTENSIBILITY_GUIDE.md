# Extensibility Guide

## Overview

NxEngine is designed with extensibility in mind. This guide explains how to extend the engine with new platforms, rendering backends, input devices, and systems.

## Design Principles for Extensions

### 1. Interface-First Design
Always define abstract interfaces in `nx_engine/` before implementing platform-specific code in `platform/`.

### 2. Service Locator Registration
New systems should integrate with the service locator for dependency management.

### 3. Event-Driven Communication
Use the event system for loose coupling between systems.

### 4. Platform Isolation
Keep platform-specific code confined to the `platform/` directory.

## Extension Points

### 1. Adding a New Rendering Backend

NxEngine currently supports OpenGL. Here's how to add Vulkan, DirectX, or other APIs:

#### Step 1: Create Interface Implementation

Create new directory structure:
```
platform/render/vulkan/
├── vulkan_render_api.h
├── vulkan_render_api.cpp
├── vulkan_render_command.h
├── vulkan_render_command.cpp
├── vulkan_shader.h
├── vulkan_shader.cpp
├── vulkan_vertex_array.h
├── vulkan_vertex_array.cpp
└── vulkan_render_system.h
```

#### Step 2: Implement Abstract Interfaces

```cpp
// vulkan_render_api.h
#pragma once
#include "render/render_api.h"

class vulkan_render_api final : public nx::render::render_api
{
public:
    vulkan_render_api() = default;
    ~vulkan_render_api() override;
    
    [[nodiscard]] nx::render::render_backend get_api() const override {
        return nx::render::render_backend::vulkan;
    }
    
    void init() override;
    void shutdown() override;
    
    nx::ref<nx::render::render_command> create_render_command() override;
    nx::ref<nx::render::shader> create_shader() override;
    
private:
    VkInstance instance_;
    VkDevice device_;
    // ... other Vulkan resources
};
```

#### Step 3: Update Service Registration

```cpp
// In main.cpp
#ifdef USE_VULKAN
    const auto renderer = services.add<render::render_system, vulkan_render_system>();
#else
    const auto renderer = services.add<render::render_system, opengl_render_system>();
#endif
```

#### Step 4: Add Build Configuration

```lua
-- In nx_engine/build.lua
filter "configurations:VulkanDebug"
    defines { "USE_VULKAN", "DEBUG" }
    links { "vulkan-1" }
```

### 2. Adding a New Window System

To add SDL, Qt, or custom windowing:

#### Step 1: Implement Window System Interface

```cpp
// platform/window/sdl_window_system.h
#pragma once
#include "window/window_system.h"

namespace window
{
    class sdl_window_system : public window_system
    {
    public:
        sdl_window_system() = default;
        ~sdl_window_system() override = default;
        
        void on_create(nx::service::locator<>* locator) override;
        void terminate() override;
        void update() override;
        
        std::shared_ptr<window_interface> create_window(
            int width, int height, std::string&& title) override;
        void destroy_window(std::shared_ptr<window_interface>) override;
        void set_current_window(const std::shared_ptr<window_interface>& window) override;
        
    private:
        std::vector<std::shared_ptr<window_interface>> windows_;
    };
}
```

#### Step 2: Implement Window Interface

```cpp
// platform/window/sdl_window.h
#pragma once
#include "window/window_interface.h"
#include <SDL.h>

class sdl_window : public window_interface
{
public:
    sdl_window(int width, int height, const std::string& title);
    ~sdl_window() override;
    
    void update() override;
    void close() override;
    void* get_raw_pointer() const override { return window_; }
    uint32_t get_id() const override { return SDL_GetWindowID(window_); }
    
private:
    SDL_Window* window_;
};
```

#### Step 3: Register with Service Locator

```cpp
const auto window_system = services.add<window::window_system, window::sdl_window_system>();
```

### 3. Adding New Input Devices

To add gamepad, touch, or VR input:

#### Step 1: Create Input Binding

```cpp
// platform/input/glfw_gamepad_binding.h
#pragma once
#include "input/input_binding.h"

class glfw_gamepad_binding : public nx::input::input_binding
{
public:
    explicit glfw_gamepad_binding(int gamepad_id, int button);
    
    void update() override;
    nx::input::key_state get_state() const override;
    
private:
    int gamepad_id_;
    int button_;
    nx::input::key_state state_;
};
```

#### Step 2: Register Input Action

```cpp
auto gamepad_action = std::make_shared<nx::input::input_action>(
    new glfw_gamepad_binding(0, GLFW_GAMEPAD_BUTTON_A), 
    "jump"
);
input_system->add_input_action(gamepad_action);
```

### 4. Adding New Core Systems

To add physics, audio, or networking:

#### Step 1: Define System Interface

```cpp
// nx_engine/physics/physics_system.h
#pragma once
#include "base/base.h"

namespace nx::physics
{
    class physics_system
    {
    public:
        virtual ~physics_system() = default;
        
        virtual void on_create(service::locator<>* locator) {}
        virtual void update(float delta_time) = 0;
        virtual void fixed_update(float fixed_delta) = 0;
        
        virtual void add_rigid_body(/* params */) = 0;
        virtual void remove_rigid_body(/* params */) = 0;
        
        // Define abstract interface for physics operations
    };
}
```

#### Step 2: Create Platform Implementation

```cpp
// platform/physics/bullet_physics_system.h
#pragma once
#include "physics/physics_system.h"
#include <btBulletDynamicsCommon.h>

class bullet_physics_system : public nx::physics::physics_system
{
public:
    bullet_physics_system();
    ~bullet_physics_system() override;
    
    void on_create(nx::service::locator<>* locator) override;
    void update(float delta_time) override;
    void fixed_update(float fixed_delta) override;
    
private:
    std::unique_ptr<btDefaultCollisionConfiguration> collision_config_;
    std::unique_ptr<btCollisionDispatcher> dispatcher_;
    std::unique_ptr<btBroadphaseInterface> broadphase_;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver_;
    std::unique_ptr<btDiscreteDynamicsWorld> world_;
};
```

#### Step 3: Integrate with Engine Loop

```cpp
// In main.cpp
const auto physics = services.add<nx::physics::physics_system, bullet_physics_system>();

while (running)
{
    input_system->update();
    physics->fixed_update(fixed_timestep);  // Fixed timestep for physics
    renderer->update();
    window_system->update();
}
```

### 5. Creating Custom Events

To add new event types for game logic:

#### Step 1: Define Event Structure

```cpp
// game/events/player_events.h
#pragma once
#include <cstdint>

namespace game::events
{
    struct player_damage
    {
        uint32_t player_id;
        float damage_amount;
        uint32_t attacker_id;
    };
    
    struct player_died
    {
        uint32_t player_id;
        uint32_t killer_id;
    };
}
```

#### Step 2: Subscribe and Publish

```cpp
// Subscribe to event
event_system->subscribe<game::events::player_damage>(&Player::on_damage, player_instance);

// Publish event
event_system->publish(game::events::player_damage{
    .player_id = 1,
    .damage_amount = 25.0f,
    .attacker_id = 2
});
```

### 6. Extending the Service Locator

#### Thread-Safe Policy

```cpp
// data_types/service_locator/policy/thread_safe_policy.h
#pragma once
#include <mutex>

namespace nx::service::policy
{
    class thread_safe
    {
    protected:
        void lock() { mutex_.lock(); }
        void unlock() { mutex_.unlock(); }
        
    private:
        std::mutex mutex_;
    };
}

// Usage:
nx::service::locator<policy::thread_safe> services;
```

#### Custom Service Factory

```cpp
template <typename T>
class service_factory
{
public:
    static std::shared_ptr<T> create()
    {
        // Custom creation logic
        auto service = std::make_shared<T>();
        service->initialize();
        return service;
    }
};
```

## Best Practices for Extensions

### 1. Follow Existing Patterns
Study existing implementations (like `glfw_window_system`) before creating new extensions.

### 2. Minimize Dependencies
Keep platform-specific dependencies isolated. Don't let them leak into core engine code.

### 3. Use Forward Declarations
Reduce compilation dependencies by forward-declaring types in headers.

```cpp
// Good
class GLFWwindow; // Forward declaration

class glfw_window
{
    GLFWwindow* window_; // Pointer to opaque type
};

// Better (for complete hiding)
class glfw_window
{
    struct impl;
    std::unique_ptr<impl> pimpl_; // Pimpl idiom
};
```

### 4. Document Your Extensions
Add documentation for:
- How to build with the new extension
- Dependencies required
- Configuration options
- Usage examples

### 5. Test Thoroughly
- Unit tests for core logic
- Integration tests with other systems
- Platform-specific testing

### 6. Performance Considerations
- Profile your implementation
- Avoid allocations in hot paths
- Consider cache-friendly data layouts
- Use batch operations where possible

## Extension Checklist

When adding a new system or platform support:

- [ ] Define abstract interface in `nx_engine/`
- [ ] Implement platform-specific version in `platform/`
- [ ] Add service locator registration
- [ ] Create necessary events
- [ ] Update build system (premake/cmake)
- [ ] Add documentation
- [ ] Write tests
- [ ] Update README with new dependencies
- [ ] Profile performance
- [ ] Test on target platform

## Examples

### Complete Example: Adding Audio System

```cpp
// 1. Define interface (nx_engine/audio/audio_system.h)
namespace nx::audio
{
    class audio_system
    {
    public:
        virtual ~audio_system() = default;
        virtual void play_sound(const std::string& path, float volume = 1.0f) = 0;
        virtual void play_music(const std::string& path, bool loop = true) = 0;
        virtual void stop_music() = 0;
        virtual void set_master_volume(float volume) = 0;
    };
}

// 2. Implement (platform/audio/openal_audio_system.h)
class openal_audio_system : public nx::audio::audio_system
{
public:
    openal_audio_system();
    ~openal_audio_system() override;
    
    void play_sound(const std::string& path, float volume) override;
    void play_music(const std::string& path, bool loop) override;
    void stop_music() override;
    void set_master_volume(float volume) override;
    
private:
    ALCdevice* device_;
    ALCcontext* context_;
};

// 3. Register in main.cpp
const auto audio = services.add<nx::audio::audio_system, openal_audio_system>();

// 4. Use
audio->play_sound("assets/sounds/explosion.wav", 0.8f);
```

## Common Pitfalls

### 1. Breaking Abstraction
**Don't:** Expose platform types in core interfaces
```cpp
// Bad
class window_system
{
    GLFWwindow* get_glfw_window(); // Platform-specific type leaked!
};
```

**Do:** Keep interfaces abstract
```cpp
// Good
class window_system
{
    void* get_raw_pointer() const; // Generic pointer
};
```

### 2. Tight Coupling
**Don't:** Directly instantiate platform types in core code
```cpp
// Bad (in nx_engine/ code)
auto window = std::make_shared<glfw_window>();
```

**Do:** Use dependency injection
```cpp
// Good
auto window_system = services.get<window::window_system>();
auto window = window_system->create_window(800, 600, "Game");
```

### 3. Platform Assumptions
**Don't:** Assume specific platform features
```cpp
// Bad
#ifdef _WIN32
    // Windows-only code in core engine
#endif
```

**Do:** Abstract platform differences
```cpp
// Good - define interface that works on all platforms
class file_system
{
    virtual std::string get_executable_path() = 0;
};
```

## Resources

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)
- [API Design Principles](https://www.youtube.com/watch?v=zL-vn_pGGgY)

## Getting Help

When extending the engine, consider:
1. Reviewing existing implementations for patterns
2. Reading the architecture documentation
3. Opening a discussion issue for design decisions
4. Submitting a draft PR for feedback
