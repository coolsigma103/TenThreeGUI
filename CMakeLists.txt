cmake_minimum_required(VERSION 3.21)

project(TenThreeGUI VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(external)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c src/*.h)

add_library(TTGUI SHARED ${SOURCES})

target_link_libraries(TTGUI PRIVATE glad glfw stb)
target_include_directories(TTGUI PRIVATE external src)
