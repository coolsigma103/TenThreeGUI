cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -fno-omit-frame-pointer")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(WIN32)
    set(Python_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/.venv/Scripts/python.exe")
else()
    set(Python_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/.venv/bin/python")
endif()


project(TenThreeGUI VERSION 1.0 LANGUAGES CXX C)

# Point CMake to your virtual environment
# Replace the path with your .venv path
set(Python3_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.venv")

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

execute_process(
    COMMAND "${Python_EXECUTABLE}" -c "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
find_package(pybind11 REQUIRED)


find_package(glfw3 CONFIG REQUIRED)

# Glad
add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c")
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Stb
add_library(stb STATIC "${CMAKE_CURRENT_SOURCE_DIR}/stb_impl/stb_impl.cpp")
target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Sources
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Pybind11 module
pybind11_add_module(TTGUI ${SOURCES})

# Link pybind11 properly
target_link_libraries(TTGUI PUBLIC
    glad
    glfw
    stb
    ${Python3_LIBRARIES}
)

# Include your source directory
target_include_directories(TTGUI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Precompile pybind11 header
target_precompile_headers(TTGUI PUBLIC <pybind11/pybind11.h>)

set_target_properties(TTGUI PROPERTIES  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")