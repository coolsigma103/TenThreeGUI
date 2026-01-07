#pragma once

#include "maths/vector.hpp"
#include <pybind11/pybind11.h>
class Frame;

class Component
{
public:
    Vector2 position;
    Vector2 size;

    Component();
    ~Component();

    virtual void update();
    virtual void render(Frame* frame);
};

namespace py = pybind11;

inline void PY_COMPONENT_HPP(py::class_<Component>& component)
{
    component.def(py::init<>())
        .def("update", &Component::update)
        .def("render", &Component::render)
        .def_readwrite("position", &Component::position)
        .def_readwrite("size", &Component::size);
}