# NxEngine Architecture Documentation

## Overview

NxEngine is a C++20 game engine built with modern C++ practices, featuring a modular architecture that separates core engine functionality from platform-specific implementations.

## Architecture Principles

### 1. Separation of Concerns
The engine follows a clear separation between:
- **Core Engine (`nx_engine/`)**: Platform-agnostic abstractions and interfaces
- **Platform Layer (`platform/`)**: Platform-specific implementations (currently GLFW/OpenGL)
- **Vendors (`vendors/`)**: Third-party dependencies

### 2. Interface-Based Design
The engine uses abstract interfaces for major systems, enabling:
- Multiple platform implementations
- Easy swapping of rendering backends
- Better testability through dependency injection

### 3. Service Locator Pattern
A custom service locator (`nx::service::locator`) manages system dependencies:
- Type-safe service registration and retrieval
- Optional lifecycle callback (`on_create`)
- Support for interface-to-implementation mapping

## System Architecture

### Core Systems

#### 1. Window System (`window/`)
- **Interface**: `window_system` - Abstract window management
- **Implementation**: `glfw_window_system` - GLFW-based implementation
- **Responsibilities**:
  - Window creation and lifecycle management
  - Event broadcasting through event system
  - Context management

#### 2. Render System (`render/`)
- **Core Components**:
  - `render_system` - Main rendering coordinator
  - `render_api` - Abstract rendering API interface
  - `renderer` - High-level rendering abstraction
  - `camera` - View and projection management
  - `shader`, `vertex_array`, `buffers` - Rendering primitives
- **Implementation**: `opengl_render_system` (OpenGL 4.5 Core)
- **Responsibilities**:
  - Scene rendering coordination
  - Graphics API abstraction
  - Resource management (shaders, textures, models)

#### 3. Input System (`input/`)
- **Core Components**:
  - `input_system` - Input management
  - `input_action` - Action-based input abstraction
  - `input_binding` - Device-specific input binding
- **Implementation**: GLFW keyboard and mouse bindings
- **Responsibilities**:
  - Input polling and state management
  - Action-based input mapping
  - Cross-platform input abstraction

#### 4. Event System (`event/`)
- **Core**: `event_system` - Type-safe event pub/sub system
- **Features**:
  - Type-safe event handlers using templates
  - Support for member functions and static functions
  - Event subscription/unsubscription
- **Usage**: Window events, input events, custom game events

#### 5. Logging System (`log/`)
- **Core**: `logger` - Structured logging with levels
- **Features**:
  - Multiple log levels (trace, debug, info, warning, error, critical)
  - Color-coded console output
  - Source location tracking (C++20 `std::source_location`)
  - Formatted logging with `std::format`

### Data Types

#### Service Locator (`data_types/service_locator/`)
- Template-based dependency injection container
- Type-indexed service storage
- Thread-safety policy support (currently not thread-safe)
- Lifecycle hooks for service initialization

### Base Utilities (`base/`)
- Smart pointer aliases: `nx::ref<T>` (shared_ptr), `nx::scope<T>` (unique_ptr)
- Factory functions: `create_ref<T>()`, `create_scope<T>()`

## Dependency Flow

```
main.cpp
  ↓
nx::service::locator
  ↓
├─→ window_system (glfw_window_system)
│     ↓
│   window_interface (glfw_window)
│     ↓
│   event_system (window events)
│
├─→ input_system (glfw_input_system)
│     ↓
│   input_action
│     ↓
│   input_binding (keyboard/mouse)
│
└─→ render_system
      ↓
    ├─→ render_api (opengl_render_api)
    ├─→ renderer
    ├─→ camera
    └─→ shader, model, textures
```

## Build System

### Premake5 Configuration
- **Workspace**: "NxEngine"
- **Language**: C++20
- **Toolset**: MSVC (Windows), can be extended for other platforms
- **Configurations**: Debug, Release
- **Architecture**: x86_64
- **Build Output**: `build/bin/{arch}-{config}/`
- **Intermediate**: `build/obj/{arch}-{config}/`

### Dependencies
- **GLFW**: Window and input management
- **GLAD**: OpenGL loader
- **GLM**: Mathematics library
- **ImGui**: Immediate mode GUI (integrated but not yet used in main)
- **Assimp**: 3D model loading

## Platform Abstraction

### Current Platform Support
- **Windows**: Full support (GLFW + OpenGL)
- **Linux/macOS**: Partial support (GLFW build configured, but not tested)

### Abstraction Strategy
1. Define abstract interfaces in `nx_engine/`
2. Implement platform-specific versions in `platform/{api}/`
3. Use service locator to inject appropriate implementation
4. Example: `window_system` → `glfw_window_system`

## Design Patterns

### 1. Service Locator
- **Location**: `data_types/service_locator/locator.h`
- **Purpose**: Centralized service management
- **Usage**: `services.add<Interface, Implementation>()`

### 2. Observer Pattern
- **Location**: `event/event_system.h`
- **Purpose**: Decoupled event notification
- **Usage**: `events->subscribe<EventType>(&handler)`

### 3. Strategy Pattern
- **Location**: Render system, Input system
- **Purpose**: Swappable algorithms/implementations
- **Example**: Different render APIs, input backends

### 4. Facade Pattern
- **Location**: `render_system`, `window_system`
- **Purpose**: Simplified interface to complex subsystems

## Strengths

1. **Clean Separation**: Core vs Platform code well separated
2. **Modern C++**: C++20 features, smart pointers, move semantics
3. **Type Safety**: Template-based service locator and event system
4. **Extensibility**: Easy to add new platforms or render backends
5. **Logging**: Comprehensive logging with source location tracking

## Areas for Improvement

See [CODE_QUALITY.md](CODE_QUALITY.md) and [EXTENSIBILITY_GUIDE.md](EXTENSIBILITY_GUIDE.md) for detailed recommendations.

## Future Considerations

1. **ECS (Entity Component System)**: For better game object management
2. **Asset Management**: Centralized asset loading and caching
3. **Scene Graph**: Hierarchical scene representation
4. **Physics Integration**: Add physics system abstraction
5. **Audio System**: Add audio subsystem
6. **Scripting**: Lua or other scripting language support
7. **Multi-threading**: Thread-safe service locator and parallel rendering
8. **Serialization**: Save/load game state and editor functionality
