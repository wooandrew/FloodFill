# CMakeLists.txt : src
cmake_minimum_required(VERSION 3.8)

include_directories(... ${CMAKE_CURRENT_SOURCE_DIR}/../includes)

find_package(OpenGL REQUIRED)

# Main Executable
add_executable(main "main.cpp")

add_library(

    Engine STATIC

    # Main
    Engine/engine.hpp          Engine/engine.cpp
)


target_link_libraries(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/glfw3.lib)

add_library(GLAD STATIC ${CMAKE_CURRENT_SOURCE_DIR}/../includes/GLAD/src/glad.c)
target_link_libraries(main PRIVATE GLAD)
