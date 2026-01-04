#pragma once
#include "module.hpp"
#include <memory>
#include <pybind11/pybind11.h>

class Application
{
    bool shouldClose = false;

    GLFWwindow* masterWindow = nullptr;
    std::vector<Frame*> frames;

    friend class Frame;

public:
    Application();
    ~Application();
    void run();
};

inline void PY_APPLICATION_HPP(py::module_& m)
{
    pybind11::class_<Application>(m, "Application")
        .def(pybind11::init<>())
        .def("run", &Application::run);
}