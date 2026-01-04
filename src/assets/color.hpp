#pragma once

#include "../maths/vector.hpp"
#include <pybind11/cast.h>
#include <pybind11/pybind11.h>

struct Color
{
    float r, g, b, a;

    static Vector4 toPipelineColor(const Color& color)
    {
        return Vector4{color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a};
    }

    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) : r(r), g(g), b(b), a(a)
    {
    }
    Color(const std::string& hexCode) { fromHex(hexCode); }
    void fromHex(const std::string& hex)
    {
        if (hex.empty() || hex[0] != '#')
            throw std::invalid_argument("Hex color must start with #");

        std::string h = hex.substr(1);

        if (h.size() != 6 && h.size() != 8)
            throw std::invalid_argument("Hex color must be #RRGGBB or #RRGGBBAA");

        r = static_cast<float>(std::stoi(h.substr(0, 2), nullptr, 16));
        g = static_cast<float>(std::stoi(h.substr(2, 2), nullptr, 16));
        b = static_cast<float>(std::stoi(h.substr(4, 2), nullptr, 16));

        if (h.size() == 8)
            a = static_cast<float>(std::stoi(h.substr(6, 2), nullptr, 16)) / 255.0f;
        else
            a = 1.0f;
    }
    std::string getHexCode(bool includeAlpha = true) const
    {
        char buffer[12];
        if (includeAlpha)
            snprintf(buffer, sizeof(buffer), "#%02X%02X%02X%02X", static_cast<int>(r),
                     static_cast<int>(g), static_cast<int>(b), static_cast<int>(a * 255.0f));
        else
            snprintf(buffer, sizeof(buffer), "#%02X%02X%02X", static_cast<int>(r),
                     static_cast<int>(g), static_cast<int>(b));
        return std::string(buffer);
    }
};

struct Color3 : Color
{
    Color3(float r = 0.0f, float g = 0.0f, float b = 0.0f) : Color(r, g, b) {}
    Color3(const std::string& hexCode) : Color(hexCode) {}
    std::string getHexCode() const { return Color::getHexCode(false); }
};

namespace py = pybind11;

inline void PY_COLOR_HPP(pybind11::module_& m)
{
    py::class_<Color>(m, "Color")
        .def(py::init<float, float, float, float>(), py::arg("r") = 0.0f, py::arg("g") = 0.0f,
             py::arg("b") = 0.0f, py::arg("a") = 1.0f)
        .def(py::init<std::string>(), py::arg("hexCode"))
        .def_readwrite("r", &Color::r)
        .def_readwrite("g", &Color::g)
        .def_readwrite("b", &Color::b)
        .def_readwrite("a", &Color::a)
        .def("getHexCode", &Color::getHexCode, py::arg("includeAlpha") = true)
        .def("fromHex", &Color::fromHex)
        .def("__repr__", [](const Color& c) { return c.getHexCode(); });
    py::class_<Color3, Color>(m, "Color3")
        .def(py::init<float, float, float>(), py::arg("r") = 0.0f, py::arg("g") = 0.0f,
             py::arg("b") = 0.0f)
        .def(py::init<std::string>(), py::arg("hexCode"))
        .def_readwrite("r", &Color3::r)
        .def_readwrite("g", &Color3::g)
        .def_readwrite("b", &Color3::b)
        .def("getHexCode", &Color3::getHexCode)
        .def("fromHex", &Color3::fromHex)
        .def("__repr__", [](const Color3& c) { return c.getHexCode(); });
}