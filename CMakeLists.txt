cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MyProject VERSION 1.0 LANGUAGES CXX C)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

find_package(glfw3 CONFIG REQUIRED)

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c")
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



