find_package(OpenGL REQUIRED)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(stb_impl)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
  OUTPUT_VARIABLE pybind11_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(pybind11 REQUIRED)