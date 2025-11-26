# NxEngine

A modern C++20 game engine with a focus on clean architecture, extensibility, and cross-platform support.

## Features

- **Modern C++20**: Utilizes latest C++ features including concepts, `std::format`, and `std::source_location`
- **Modular Architecture**: Clean separation between core engine and platform-specific implementations
- **Multiple Rendering Backends**: Currently supports OpenGL 4.5+, extensible to Vulkan, DirectX
- **Cross-Platform**: Windows support with Linux/macOS compatibility in progress
- **Event-Driven**: Type-safe event system for decoupled component communication
- **Service Locator**: Dependency injection for flexible system management
- **3D Model Loading**: Assimp integration for loading various 3D model formats
- **Modern OpenGL**: Core profile with vertex arrays, shaders, and textures

## Architecture

NxEngine follows a layered architecture with clean separation between core engine and platform-specific code. For detailed information, see [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Documentation

- **[Architecture Guide](docs/ARCHITECTURE.md)**: System design and architecture overview
- **[Code Quality Assessment](docs/CODE_QUALITY.md)**: Code quality analysis and improvement recommendations
- **[Coding Standards](docs/CODING_STANDARDS.md)**: Coding conventions and best practices
- **[Extensibility Guide](docs/EXTENSIBILITY_GUIDE.md)**: How to extend the engine with new systems and platforms

## Prerequisites

### Windows
- **Visual Studio 2022** or later with C++20 support
- **Premake5** - [Download here](https://premake.github.io/download)
- **Git** with submodule support

### Linux (Experimental)
- **GCC 10+** or **Clang 11+** with C++20 support
- **Premake5**
- Development libraries: `libglfw3-dev`, `libgl1-mesa-dev`

## Building

### Quick Start (Windows)

```bash
# Clone the repository with submodules
git clone --recursive https://github.com/Enzx/nxengine.git
cd nxengine

# Generate Visual Studio solution
premake5 vs2022

# Open and build the solution
start NxEngine.sln
```

### Build Configurations

- **Debug**: Full debug symbols, no optimization, assertions enabled
- **Release**: Optimizations enabled, minimal debug info

## Project Structure

```
nxengine/
├── assets/              # Game assets (models, textures, shaders)
├── docs/                # Documentation
├── nx_engine/           # Core engine (platform-agnostic)
├── platform/            # Platform-specific implementations
├── vendors/             # Third-party dependencies
└── premake5.lua         # Build configuration
```

## Dependencies

- **GLFW 3.x**: Window and input management
- **GLAD**: OpenGL loader
- **GLM**: Mathematics library
- **Assimp**: 3D model loading
- **ImGui**: Immediate mode GUI

All dependencies are included as submodules or vendored.

## Contributing

Contributions are welcome! Please follow the [Coding Standards](docs/CODING_STANDARDS.md) and existing architecture patterns.

## System Requirements

### Minimum
- **OS**: Windows 10, Linux (Ubuntu 20.04+), macOS 10.15+
- **GPU**: OpenGL 4.5 capable graphics card
- **RAM**: 4GB

### Recommended
- **OS**: Windows 11, Linux (Latest), macOS (Latest)
- **GPU**: Modern GPU with OpenGL 4.6+ support
- **RAM**: 8GB+
