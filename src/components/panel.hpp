#pragma once

#include "../assets/color.hpp"
#include "../component.hpp"
#include <pybind11/pybind11.h>

class Panel : public Component
{
public:
    Color color;
    Panel();
    virtual ~Panel();

    void render(Frame* frame) override;
};

namespace py = pybind11;
inline void PY_PANEL_HPP(py::class_<Panel, Component>& panel)
{
    panel.def(py::init<>());
}

constexpr const char* panelFragmentShaderSource = R"glsl(
        #version 330 core

        out vec4 FragColor;

        in vec2 TexCoord;

        uniform vec4 panelColor;

        void main()
        {
            FragColor = panelColor;
        }
        )glsl";