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

find_package(Python REQUIRED COMPONENTS Interpreter Development Development.Module)

execute_process(
  COMMAND ${Python_EXECUTABLE} -m pybind11 --cmakedir
  OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")

find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(external)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c src/*.h)

pybind11_add_module(TTGUI ${SOURCES})

target_link_libraries(TTGUI PRIVATE glad glfw stb)
target_include_directories(TTGUI PRIVATE external src)