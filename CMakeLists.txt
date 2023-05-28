# CMakeLists.txt : CMake project for Flood Fill algorithm implementation

cmake_minimum_required(VERSION 3.8)
project(FloodFill VERSION 1.0 DESCRIPTION "Flood Fill implementation")
add_subdirectory(src)

find_package(OpenGL REQUIRED)

include_directories(... ${CMAKE_CURRENT_SOURCE_DIR}/includes)
