#pragma once
#include <pybind11/pybind11.h>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include <stb/stb_image.h>
#include <stb/stb_truetype.h>
// #include <stb/stb_vorbis.c>

namespace py = pybind11;

class Application;
class Frame;
class Component;
class Renderer;