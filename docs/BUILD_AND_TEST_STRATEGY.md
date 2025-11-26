# Build and Test Strategy

## Overview

This document outlines the recommended build system, testing infrastructure, and continuous integration strategy for NxEngine.

## Current State

### Build System
- **Tool**: Premake5
- **Primary Target**: Visual Studio 2022 (Windows)
- **Status**: Functional for Windows, partial support for Linux/macOS

### Testing
- **Status**: No testing infrastructure currently in place
- **Risk**: High - no automated verification of functionality

## Recommended Build Strategy

### Phase 1: Enhance Current Build System (Immediate)

#### 1.1 Improve Premake Configuration

**Add Build Options:**
```lua
-- In premake5.lua
newoption {
    trigger = "renderer",
    value = "API",
    description = "Choose rendering backend",
    allowed = {
        { "opengl", "OpenGL renderer (default)" },
        { "vulkan", "Vulkan renderer" }
    },
    default = "opengl"
}

newoption {
    trigger = "with-tests",
    description = "Build with unit tests"
}
```

**Configuration Matrix:**
- Debug / Release
- OpenGL / Vulkan (future)
- With/Without Tests
- With/Without Examples

#### 1.2 Add CMake Support (Optional, Medium Priority)

Many developers are more familiar with CMake than Premake. Consider parallel CMake support:

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(NxEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(NX_BUILD_TESTS "Build tests" OFF)
option(NX_BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(vendors/GLFW)
add_subdirectory(vendors/glad)
# ... other dependencies

add_subdirectory(nx_engine)
add_subdirectory(platform)

if(NX_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
```

### Phase 2: Package Management (Short-term)

#### Option A: vcpkg (Recommended for Windows)

```json
// vcpkg.json
{
  "name": "nxengine",
  "version-string": "0.1.0",
  "dependencies": [
    "glfw3",
    "glad",
    "glm",
    "assimp",
    "imgui"
  ]
}
```

**Benefits:**
- Automated dependency management
- Version control for dependencies
- Cross-platform support
- Integration with CMake/MSBuild

#### Option B: Conan (Alternative)

```python
# conanfile.txt
[requires]
glfw/3.3.8
glm/0.9.9.8
assimp/5.2.5

[generators]
premake
cmake
```

### Phase 3: Cross-Platform Testing (Medium-term)

#### Platform Build Matrix

| Platform | Compiler | Status | Priority |
|----------|----------|--------|----------|
| Windows | MSVC 2022 | ✅ Working | High |
| Windows | Clang-cl | ❓ Untested | Medium |
| Linux | GCC 10+ | ⚠️ Partial | High |
| Linux | Clang 11+ | ⚠️ Partial | Medium |
| macOS | Apple Clang | ❓ Untested | Low |

**Action Items:**
- [ ] Test Linux builds with GCC and Clang
- [ ] Verify macOS compatibility
- [ ] Add platform-specific build instructions
- [ ] Document platform-specific issues

## Testing Strategy

### Phase 1: Testing Infrastructure Setup (HIGH PRIORITY)

#### 1.1 Choose Testing Framework

**Recommendation: Catch2**
- Header-only, easy integration
- Modern C++ friendly
- Good documentation
- BDD-style tests

**Alternative: Google Test**
- Industry standard
- Extensive features
- Better for large test suites

#### 1.2 Initial Test Structure

```
tests/
├── unit/                    # Unit tests
│   ├── service_locator_test.cpp
│   ├── event_system_test.cpp
│   ├── camera_test.cpp
│   └── ...
├── integration/             # Integration tests
│   ├── window_render_test.cpp
│   ├── input_system_test.cpp
│   └── ...
├── mocks/                   # Mock implementations
│   ├── mock_window_system.h
│   ├── mock_render_api.h
│   └── ...
└── CMakeLists.txt / build.lua
```

#### 1.3 Example Test Implementation

**Using Catch2:**

```cpp
// tests/unit/service_locator_test.cpp
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "data_types/service_locator/locator.h"

class test_service
{
public:
    int value = 42;
};

TEST_CASE("Service Locator - Add and Get Service", "[service_locator]")
{
    nx::service::locator<> locator;
    
    SECTION("Can add and retrieve service")
    {
        auto service = locator.add<test_service>();
        REQUIRE(service != nullptr);
        REQUIRE(service->value == 42);
    }
    
    SECTION("Retrieved service is same instance")
    {
        auto service1 = locator.add<test_service>();
        auto service2 = locator.get<test_service>();
        REQUIRE(service1 == service2);
    }
    
    SECTION("Can remove service")
    {
        locator.add<test_service>();
        locator.remove<test_service>();
        auto service = locator.get<test_service>();
        REQUIRE(service == nullptr);
    }
}
```

**Using Google Test:**

```cpp
// tests/unit/event_system_test.cpp
#include <gtest/gtest.h>
#include "event/event_system.h"

struct test_event
{
    int value;
};

class EventSystemTest : public ::testing::Test
{
protected:
    nx::event::event_system event_system;
    int received_value = 0;
    
    void on_test_event(const test_event& e)
    {
        received_value = e.value;
    }
};

TEST_F(EventSystemTest, SubscribeAndPublish)
{
    event_system.subscribe<test_event>(&EventSystemTest::on_test_event, this);
    event_system.publish(test_event{42});
    
    EXPECT_EQ(received_value, 42);
}

TEST_F(EventSystemTest, UnsubscribeStopsReceiving)
{
    event_system.subscribe<test_event>(&EventSystemTest::on_test_event, this);
    event_system.unsubscribe<test_event>(&EventSystemTest::on_test_event, this);
    event_system.publish(test_event{42});
    
    EXPECT_EQ(received_value, 0);  // Should not have changed
}
```

### Phase 2: Test Coverage (Ongoing)

#### Priority Test Areas

**High Priority:**
1. Service Locator
   - Add, get, remove operations
   - Interface-to-implementation mapping
   - Lifecycle callbacks (on_create)
   - Thread-safety policies

2. Event System
   - Subscribe/unsubscribe
   - Event publishing
   - Multiple subscribers
   - Event order

3. Input System
   - Input action creation
   - State management
   - Binding updates
   - Multiple actions

4. Camera System
   - View matrix calculation
   - Projection matrix calculation
   - Position and orientation
   - Look-at functionality

**Medium Priority:**
5. Render System Interfaces
   - Shader compilation
   - Vertex array operations
   - Buffer management

6. Window System
   - Window creation/destruction
   - Event propagation
   - Multi-window support

**Low Priority:**
7. OpenGL Implementation Details
   - Platform-specific rendering tests
   - Requires graphics context

### Phase 3: Mock Implementations

Create mocks for testing without platform dependencies:

```cpp
// tests/mocks/mock_render_api.h
#pragma once
#include "render/render_api.h"

class mock_render_api : public nx::render::render_api
{
public:
    bool init_called = false;
    bool shutdown_called = false;
    
    [[nodiscard]] nx::render::render_backend get_api() const override
    {
        return nx::render::render_backend::mock;
    }
    
    void init() override { init_called = true; }
    void shutdown() override { shutdown_called = true; }
    
    nx::ref<nx::render::render_command> create_render_command() override
    {
        return nullptr;  // Mock implementation
    }
    
    nx::ref<nx::render::shader> create_shader() override
    {
        return nullptr;  // Mock implementation
    }
};
```

### Phase 4: Integration Tests

Test system interactions:

```cpp
// tests/integration/window_render_integration_test.cpp
TEST_CASE("Window and Render System Integration", "[integration]")
{
    nx::service::locator<> services;
    
    // Use mock implementations
    auto window_system = services.add<window::window_system, mock_window_system>();
    auto render_system = services.add<render::render_system, mock_render_system>();
    
    // Test initialization order
    REQUIRE_NOTHROW(window_system->create_window(800, 600, "Test"));
    REQUIRE_NOTHROW(render_system->init());
    
    // Test integration
    window_system->update();
    render_system->update();
    
    // Verify state
    REQUIRE(render_system->is_initialized());
}
```

## Continuous Integration Strategy

### Phase 1: GitHub Actions Setup

#### Basic CI Workflow

```yaml
# .github/workflows/ci.yml
name: CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  build-windows:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v3
        with:
          submodules: recursive
      
      - name: Setup Premake
        run: |
          Invoke-WebRequest -Uri "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip" -OutFile premake.zip
          Expand-Archive premake.zip -DestinationPath .
      
      - name: Generate Project
        run: ./premake5.exe vs2022
      
      - name: Build
        run: msbuild NxEngine.sln /p:Configuration=Release /p:Platform=x64
      
      - name: Run Tests
        run: ./build/bin/x86_64-Release/nx_engine_tests.exe

  build-linux:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          submodules: recursive
      
      - name: Install Dependencies
        run: |
          sudo apt-get update
          sudo apt-get install -y libglfw3-dev libgl1-mesa-dev
      
      - name: Setup Premake
        run: |
          wget https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz
          tar -xvf premake-5.0.0-beta2-linux.tar.gz
      
      - name: Generate Makefile
        run: ./premake5 gmake2
      
      - name: Build
        run: |
          cd build
          make config=release_x86_64
      
      - name: Run Tests
        run: ./build/bin/x86_64-Release/nx_engine_tests

  code-quality:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Run clang-format
        run: |
          find nx_engine platform -name "*.cpp" -o -name "*.h" | xargs clang-format --dry-run --Werror
      
      - name: Run clang-tidy
        run: |
          clang-tidy nx_engine/**/*.cpp -- -std=c++20
```

### Phase 2: Code Quality Checks

#### Static Analysis
- **clang-tidy**: Catch common issues
- **cppcheck**: Additional static analysis
- **clang-format**: Enforce formatting

#### Coverage Reporting
- **lcov/gcov**: Code coverage for GCC/Clang
- **OpenCppCoverage**: Coverage for MSVC
- **Codecov/Coveralls**: Online coverage reporting

#### Example Coverage Workflow

```yaml
# .github/workflows/coverage.yml
name: Coverage

on: [push, pull_request]

jobs:
  coverage:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Build with Coverage
        run: |
          cmake -B build -DCMAKE_BUILD_TYPE=Debug -DNX_COVERAGE=ON
          cmake --build build
      
      - name: Run Tests
        run: ./build/tests/nx_engine_tests
      
      - name: Generate Coverage Report
        run: |
          lcov --capture --directory build --output-file coverage.info
          lcov --remove coverage.info '/usr/*' '*/vendors/*' --output-file coverage.info
      
      - name: Upload to Codecov
        uses: codecov/codecov-action@v3
        with:
          files: ./coverage.info
```

### Phase 3: Advanced CI/CD

#### Automated Releases
```yaml
# .github/workflows/release.yml
name: Release

on:
  push:
    tags:
      - 'v*'

jobs:
  release:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Build Release
        run: |
          premake5 vs2022
          msbuild NxEngine.sln /p:Configuration=Release
      
      - name: Package
        run: |
          mkdir release
          copy build\bin\x86_64-Release\nx_engine.exe release\
          copy -r assets release\
      
      - name: Create Release
        uses: softprops/action-gh-release@v1
        with:
          files: release/*
```

## Performance Testing

### Benchmarking Strategy

**Use Google Benchmark or Catch2 Benchmark:**

```cpp
// tests/benchmarks/render_benchmark.cpp
#include <benchmark/benchmark.h>
#include "render/camera.h"

static void BM_CameraViewMatrixUpdate(benchmark::State& state)
{
    nx::render::camera camera;
    camera.set_position(glm::vec3(0, 0, 10));
    
    for (auto _ : state)
    {
        camera.look_at(glm::vec3(0, 0, 0));
        benchmark::DoNotOptimize(camera.get_view_matrix());
    }
}

BENCHMARK(BM_CameraViewMatrixUpdate);
```

### Profiling Integration
- **Tracy Profiler**: Real-time profiling
- **Optick**: Frame profiler
- **Built-in timers**: Custom performance metrics

## Documentation Build

### API Documentation with Doxygen

```bash
# Doxyfile
PROJECT_NAME = "NxEngine"
OUTPUT_DIRECTORY = docs/api
INPUT = nx_engine platform
RECURSIVE = YES
GENERATE_HTML = YES
GENERATE_LATEX = NO
EXTRACT_ALL = YES
```

### CI Documentation Build

```yaml
- name: Build Documentation
  run: doxygen Doxyfile

- name: Deploy to GitHub Pages
  uses: peaceiris/actions-gh-pages@v3
  with:
    github_token: ${{ secrets.GITHUB_TOKEN }}
    publish_dir: ./docs/api/html
```

## Implementation Checklist

### Immediate (Week 1-2)
- [ ] Add Catch2 or Google Test framework
- [ ] Create basic test structure
- [ ] Write tests for service locator
- [ ] Write tests for event system
- [ ] Set up basic GitHub Actions CI

### Short-term (Month 1)
- [ ] Achieve 50%+ code coverage
- [ ] Add mock implementations
- [ ] Linux build testing
- [ ] clang-format integration
- [ ] clang-tidy integration

### Medium-term (Month 2-3)
- [ ] Integration tests
- [ ] Performance benchmarks
- [ ] Code coverage reporting
- [ ] Cross-platform CI matrix
- [ ] CMake support (optional)

### Long-term (Quarter 1)
- [ ] 80%+ code coverage
- [ ] Automated releases
- [ ] API documentation generation
- [ ] vcpkg/Conan integration
- [ ] Advanced profiling setup

## Conclusion

A robust build and test strategy is essential for maintaining code quality and enabling confident refactoring. The phased approach allows incremental improvement without overwhelming the development process.

**Next Steps:**
1. Choose testing framework (Catch2 recommended)
2. Set up basic test infrastructure
3. Write initial unit tests for core systems
4. Configure GitHub Actions for CI
5. Gradually increase test coverage
