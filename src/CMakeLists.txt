# CMakeLists.txt : src
cmake_minimum_required(VERSION 3.8)

include_directories(... ${CMAKE_CURRENT_SOURCE_DIR}/../includes)

find_package(OpenGL REQUIRED)

# Main Executable
add_executable(main "main.cpp")

add_library(

    Engine STATIC

    # Engine
    Engine/engine.hpp                   Engine/engine.cpp
    
    # Engine/Inputs
    Engine/Inputs/keyboard.hpp          Engine/Inputs/keyboard.cpp
    Engine/Inputs/mouse.hpp             Engine/Inputs/mouse.cpp

    # Engine/Graphics
    Engine/Graphics/graphics.hpp        Engine/Graphics/graphics.cpp
    Engine/Graphics/renderer.hpp        Engine/Graphics/renderer.cpp
    Engine/Graphics/camera.hpp          Engine/Graphics/camera.cpp
    Engine/Graphics/vertex.hpp          Engine/Graphics/vertex.cpp
    Engine/Graphics/buffer.hpp          Engine/Graphics/buffer.cpp
    Engine/Graphics/shader.hpp          Engine/Graphics/shader.cpp
)


target_link_libraries(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/glfw3.lib)

add_library(GLAD STATIC ${CMAKE_CURRENT_SOURCE_DIR}/../includes/GLAD/src/glad.c)
target_link_libraries(main PRIVATE GLAD)

target_link_libraries(main PRIVATE Engine)
