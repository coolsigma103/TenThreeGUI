#pragma once

#include <algorithm>
#include <chrono>
#include <mutex>
#include <pybind11/pybind11.h>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

class Frame;
class Renderer;

class Application
{
    Renderer* renderer = nullptr;

    bool shouldClose = false;
    std::mutex mtx;

    GLFWwindow* masterWindow = nullptr;
    std::vector<Frame*> frames;

    friend class Frame;

public:
    Application();
    ~Application();
    void run();

    Renderer* getRenderer();
};

namespace py = pybind11;

inline void PY_APPLICATION_HPP(py::class_<Application>& application)
{
    application.def(py::init<>()).def("run", &Application::run);
}