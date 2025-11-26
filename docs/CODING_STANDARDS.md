# NxEngine Coding Standards

## Overview

This document establishes coding standards for the NxEngine project to ensure consistency, readability, and maintainability.

## Language and Compiler

- **C++ Standard**: C++20
- **Primary Compiler**: MSVC (Visual Studio 2022), with GCC/Clang support
- **Warning Level**: Treat warnings as errors in CI builds

## Naming Conventions

### General Rules
- Use descriptive, meaningful names
- Avoid abbreviations unless widely recognized (e.g., `id`, `api`, `ui`)
- Prefer readability over brevity

### Files
```cpp
snake_case.h          // Header files
snake_case.cpp        // Implementation files
```

**Examples:**
- `render_system.h`
- `window_interface.h`
- `glfw_input_system.cpp`

### Namespaces
```cpp
namespace lower_case  // Snake case for namespaces
{
    namespace nested  // Nested namespaces also snake case
    {
    }
}
```

**Examples:**
```cpp
namespace nx
{
    namespace render
    {
        class shader;
    }
}
```

### Classes and Structs
```cpp
class snake_case      // Snake case for classes
{
};

struct snake_case     // Snake case for structs
{
};
```

**Examples:**
- `render_system`
- `window_interface`
- `input_action`
- `event_system`

### Functions and Methods
```cpp
void function_name()  // Snake case for functions
{
}
```

**Examples:**
```cpp
void update();
void on_window_resize(const resize_event& event);
std::shared_ptr<window_interface> create_window();
[[nodiscard]] int get_width() const;
```

### Variables

#### Local Variables
```cpp
int local_variable = 0;        // Snake case
auto another_value = 10;       // Snake case
```

#### Member Variables
```cpp
class example
{
private:
    int member_variable_;       // Snake case with trailing underscore
    std::string name_;          // Trailing underscore indicates member
    static int class_variable_; // Static members also with underscore
};
```

#### Constants
```cpp
constexpr int MAX_BUFFER_SIZE = 1024;  // UPPER_CASE for compile-time constants
const float default_fov = 45.0f;       // Snake case for runtime constants
```

#### Global Variables
```cpp
// Avoid global variables when possible
// If necessary, use namespace scope and prefix with g_
namespace globals
{
    inline int g_frame_count = 0;
}
```

### Enums
```cpp
enum class log_level      // Snake case for enum class
{
    trace,                // Snake case for enumerators
    debug,
    info,
    warning,
    error,
    critical
};

// Usage
log_level level = log_level::debug;
```

### Template Parameters
```cpp
template <typename T>            // Use typename, not class
template <typename TMessage>     // Prefix with 'T' for clarity if helpful
template <typename Interface>    // Or use descriptive name

// Concept names
template <std::integral T>       // Concepts use PascalCase by convention
```

### Macros
```cpp
#define NX_LOG_DEBUG(msg)       // UPPER_CASE with prefix
#define GL_CHECK_ERROR()        // UPPER_CASE
```

## Formatting

### Indentation
- **4 spaces** (no tabs)
- Consistent throughout the codebase

### Braces
```cpp
// Allman style (opening brace on new line) for functions and classes
void function()
{
    // code
}

class example
{
public:
    void method()
    {
        // code
    }
};

// K&R style acceptable for control structures (opening brace on same line)
if (condition) {
    // code
} else {
    // code
}

// Or Allman for consistency
if (condition)
{
    // code
}
else
{
    // code
}
```

**Choose one style and be consistent within a file.**

### Line Length
- **Preferred maximum**: 100 characters
- **Hard limit**: 120 characters
- Break long lines logically

```cpp
// Good
auto window = window_system->create_window(
    800, 
    600, 
    "My Game Window"
);

// Also acceptable
auto window = window_system->create_window(
    800, 600, "My Game Window");
```

### Whitespace

#### Around Operators
```cpp
int x = 5;           // Spaces around assignment
int y = x + 3;       // Spaces around binary operators
x += 2;              // Spaces around compound assignment
bool flag = !x;      // No space after unary operators
```

#### After Keywords
```cpp
if (condition)       // Space after 'if'
while (running)      // Space after 'while'
for (int i = 0; i < 10; ++i)  // Spaces appropriately
```

#### Function Calls
```cpp
function(arg1, arg2);           // Space after comma
function();                     // No space before parenthesis
```

#### Template Declarations
```cpp
template <typename T>           // Spaces inside angle brackets
std::vector<int> vec;          // No spaces in template instantiation
```

### Empty Lines
- One blank line between function definitions
- Two blank lines between major sections (public/private/protected)
- Blank lines to separate logical blocks within functions

```cpp
class example
{
public:
    void method1();
    void method2();


private:
    void helper1();
    void helper2();
    
    int member_;
};
```

## Comments

### File Headers
```cpp
/**
 * @file render_system.h
 * @brief Main rendering system coordinator
 * @author Your Name
 * 
 * Manages the rendering pipeline, integrates with platform-specific
 * render APIs, and coordinates scene rendering.
 */
```

### Class Documentation
```cpp
/**
 * @brief Abstract interface for window management
 * 
 * Provides platform-independent window creation, management,
 * and event handling. Platform-specific implementations should
 * inherit from this interface.
 */
class window_system
{
    // ...
};
```

### Function Documentation
```cpp
/**
 * @brief Creates a new window with specified parameters
 * @param width Window width in pixels (must be > 0)
 * @param height Window height in pixels (must be > 0)
 * @param title Window title string
 * @return Shared pointer to created window, nullptr on failure
 * @throws std::runtime_error if window creation fails
 */
virtual std::shared_ptr<window_interface> create_window(
    int width, 
    int height, 
    std::string&& title) = 0;
```

### Inline Comments
```cpp
// Use inline comments sparingly, only when code is not self-explanatory

// Calculate aspect ratio for projection matrix
float aspect = static_cast<float>(width) / static_cast<float>(height);

// DON'T: State the obvious
// Increment counter
counter++;  // Bad comment
```

### TODO Comments
```cpp
// TODO: Implement texture caching
// TODO(username): Add error handling here
// FIXME: Memory leak in destruction
// NOTE: This assumes OpenGL 4.5+
// HACK: Temporary workaround for GLFW bug
```

## Modern C++ Practices

### Smart Pointers
```cpp
// Prefer unique_ptr for exclusive ownership
std::unique_ptr<renderer> renderer_;

// Use shared_ptr only when shared ownership is needed
std::shared_ptr<window_interface> window_;

// Avoid raw pointers for ownership
// int* data = new int[100];  // Bad - use vector or unique_ptr

// Use raw pointers only for non-owning references
void process(const texture* tex);  // OK - non-owning
```

### Auto Keyword
```cpp
// Use auto to avoid repeating types
auto window = std::make_shared<glfw_window>(); // Good

// But be explicit when clarity matters
float aspect_ratio = 16.0f / 9.0f;  // Clear intent
auto result = divide(x, y);         // Less clear

// Use auto with structured bindings
for (const auto& [key, value] : map) {
    // ...
}
```

### Const Correctness
```cpp
class example
{
public:
    // Mark methods const if they don't modify state
    [[nodiscard]] int get_value() const { return value_; }
    
    // Use const references for parameters
    void set_name(const std::string& name) { name_ = name; }
    
    // Use const pointers when appropriate
    void process(const texture* tex);
    
private:
    int value_;
    std::string name_;
};

// Const member variables for immutable state
class immutable_example
{
    const int id_;  // Cannot be changed after construction
};
```

### Range-Based For Loops
```cpp
// Prefer range-based for loops
for (const auto& item : container) {
    // process item
}

// Use structured bindings with maps
for (const auto& [key, value] : map) {
    // process key and value
}

// Avoid index-based loops unless index is needed
// for (size_t i = 0; i < vec.size(); ++i)  // Use only if you need 'i'
```

### Nullptr
```cpp
// Use nullptr instead of NULL or 0
void* ptr = nullptr;  // Good
// void* ptr = NULL;  // Avoid
// void* ptr = 0;     // Avoid
```

### Explicit Constructors
```cpp
class texture
{
public:
    // Explicit to prevent implicit conversions
    explicit texture(const std::string& path);
    
    // Multi-parameter constructors don't need explicit
    texture(int width, int height);
};
```

### Delete Special Members
```cpp
class non_copyable
{
public:
    non_copyable() = default;
    
    // Delete copy operations
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
    
    // Default or implement move operations if needed
    non_copyable(non_copyable&&) noexcept = default;
    non_copyable& operator=(non_copyable&&) noexcept = default;
};
```

### [[nodiscard]]
```cpp
// Use [[nodiscard]] for functions where ignoring the return value is likely a bug
class window
{
public:
    [[nodiscard]] bool is_open() const;
    [[nodiscard]] int get_width() const;
    [[nodiscard]] std::string get_title() const;
};
```

### Structured Bindings
```cpp
// Use structured bindings for clarity
auto [width, height] = window->get_size();
auto [it, inserted] = map.insert({key, value});

// Instead of
// auto result = window->get_size();
// int width = result.first;
// int height = result.second;
```

## Error Handling

### Exceptions
```cpp
// Use exceptions for exceptional circumstances
void load_texture(const std::string& path)
{
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error(
            std::format("Texture file not found: {}", path));
    }
    // load...
}

// Document exceptions in function documentation
/**
 * @throws std::runtime_error if file not found
 * @throws std::invalid_argument if path is empty
 */
```

### Return Values
```cpp
// Use std::optional for operations that might fail
[[nodiscard]] std::optional<texture> load_texture(const std::string& path);

// Use expected-like patterns for errors with information
struct load_result
{
    bool success;
    std::string error_message;
    std::shared_ptr<texture> texture;
};
```

### Assertions
```cpp
// Use assertions for debugging, not for error handling
#include <cassert>
assert(width > 0 && "Width must be positive");

// Use engine-specific debug assertions
NX_DEBUG_ASSERT(ptr != nullptr, "Pointer must not be null");
```

## Include Guards

Use `#pragma once` for header guards (it's compiler-supported and cleaner):

```cpp
#pragma once

// Header content
```

## Include Order

```cpp
// 1. Corresponding header (for .cpp files)
#include "my_class.h"

// 2. C system headers
#include <cstdint>
#include <cstring>

// 3. C++ standard library headers
#include <string>
#include <vector>
#include <memory>

// 4. Third-party library headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

// 5. Project headers
#include "base/base.h"
#include "window/window_interface.h"
#include "render/renderer.h"

// Separate groups with blank lines
```

## Forward Declarations

Use forward declarations to reduce compilation dependencies:

```cpp
// In header file - prefer forward declarations
class window_interface;  // Forward declaration
class renderer;          // Forward declaration

class render_system
{
    void set_window(window_interface* window);  // OK - pointer
    void set_renderer(std::unique_ptr<renderer> r);  // OK - unique_ptr
};

// In implementation file - include full headers
#include "window/window_interface.h"
#include "render/renderer.h"
```

## Platform-Specific Code

### Isolate Platform Code
```cpp
// Avoid in core engine headers
#ifdef _WIN32
    // Windows code
#endif

// Instead, use abstraction
// Define interface in core, implement in platform/
```

### Use Feature Macros
```cpp
// Define features, not platforms
#ifdef NX_FEATURE_RAYTRACING
    // Raytracing code
#endif
```

## Performance Guidelines

### Pass by Reference
```cpp
// Large objects by const reference
void process(const std::vector<vertex>& vertices);

// Small objects (int, float, pointers) by value
void set_id(int id);

// Output parameters by non-const reference or pointer
void get_dimensions(int& width, int& height);
```

### Move Semantics
```cpp
// Pattern 1: Accept by value and move (good for simple cases)
void set_name(std::string name) {
    name_ = std::move(name);
}

// Pattern 2: Provide both overloads for optimal performance
void set_name(const std::string& name) {  // For lvalues - copy
    name_ = name;
}

void set_name(std::string&& name) {       // For rvalues - move
    name_ = std::move(name);
}

// Pattern 3: Perfect forwarding (template contexts)
template<typename T>
void set_value(T&& value) {
    value_ = std::forward<T>(value);
}

// Return large objects by value (RVO/NRVO will optimize)
std::vector<int> create_data() {
    std::vector<int> data;
    // populate...
    return data;  // No std::move needed - return value optimization
}
```

### Reserve Capacity
```cpp
// Reserve capacity for vectors when size is known
std::vector<vertex> vertices;
vertices.reserve(1000);
for (int i = 0; i < 1000; ++i) {
    vertices.push_back(create_vertex(i));
}
```

## Testing

### Test File Naming
```cpp
// Test files should have _test suffix
render_system_test.cpp
window_interface_test.cpp
```

### Test Case Structure
```cpp
TEST(RenderSystem, InitializesCorrectly)
{
    // Arrange
    render_system system;
    
    // Act
    system.init();
    
    // Assert
    EXPECT_TRUE(system.is_initialized());
}
```

## clang-format Configuration

Create `.clang-format` in repository root:

```yaml
Language: Cpp
BasedOnStyle: LLVM
IndentWidth: 4
UseTab: Never
ColumnLimit: 100
PointerAlignment: Left
AllowShortFunctionsOnASingleLine: Inline
AllowShortIfStatementsOnASingleLine: Never
```

## Summary Checklist

When writing code, ensure:

- [ ] Follows naming conventions (snake_case)
- [ ] Member variables have trailing underscore
- [ ] Functions are documented with purpose and parameters
- [ ] Uses smart pointers instead of raw pointers for ownership
- [ ] Const correctness is maintained
- [ ] [[nodiscard]] used for important return values
- [ ] Includes are ordered correctly
- [ ] No platform-specific code in core engine
- [ ] Exceptions are documented
- [ ] Code is self-documenting with good names
- [ ] Comments explain "why", not "what"
- [ ] Tests exist for new functionality

## Tools

### Recommended Tools
- **clang-format**: Automatic code formatting
- **clang-tidy**: Static analysis and linting
- **cppcheck**: Additional static analysis
- **include-what-you-use**: Include dependency analysis

### IDE Setup
Configure your IDE to:
- Use 4 spaces for indentation
- Remove trailing whitespace
- Add newline at end of file
- Use UTF-8 encoding without BOM
- Show whitespace characters
