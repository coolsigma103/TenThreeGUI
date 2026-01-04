#pragma once

#include <cmath>
#include <pybind11/pybind11.h>

// Vector2
class Vector2
{
public:
    float x, y;

    Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }

    Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }

    Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
};

// Vector3
class Vector3
{
public:
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }

    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }

    Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
};

// Vector4
class Vector4
{
public:
    float x, y, z, w;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}

    Vector4 operator+(const Vector4& v) const
    {
        return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    Vector4 operator-(const Vector4& v) const
    {
        return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    Vector4 operator*(float scalar) const
    {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }
};

inline void PY_VECTOR_HPP(pybind11::module_& m)
{
    pybind11::class_<Vector2>(m, "Vector2")
        .def(pybind11::init<float, float>(), pybind11::arg("x") = 0, pybind11::arg("y") = 0)
        .def_readwrite("x", &Vector2::x)
        .def_readwrite("y", &Vector2::y)
        .def("__add__", [](const Vector2& self, const Vector2& other) { return self + other; })
        .def("__sub__", [](const Vector2& self, const Vector2& other) { return self - other; })
        .def("__mul__", [](const Vector2& self, float scalar) { return self * scalar; })
        .def("__rmul__", [](const Vector2& self, float scalar) { return self * scalar; });

    pybind11::class_<Vector3>(m, "Vector3")
        .def(pybind11::init<float, float, float>(), pybind11::arg("x") = 0, pybind11::arg("y") = 0,
             pybind11::arg("z") = 0)
        .def_readwrite("x", &Vector3::x)
        .def_readwrite("y", &Vector3::y)
        .def_readwrite("z", &Vector3::z)
        .def("__add__", [](const Vector3& self, const Vector3& other) { return self + other; })
        .def("__sub__", [](const Vector3& self, const Vector3& other) { return self - other; })
        .def("__mul__", [](const Vector3& self, float scalar) { return self * scalar; })
        .def("__rmul__", [](const Vector3& self, float scalar) { return self * scalar; });

    pybind11::class_<Vector4>(m, "Vector4")
        .def(pybind11::init<float, float, float, float>(), pybind11::arg("x") = 0,
             pybind11::arg("y") = 0, pybind11::arg("z") = 0, pybind11::arg("w") = 0)
        .def_readwrite("x", &Vector4::x)
        .def_readwrite("y", &Vector4::y)
        .def_readwrite("z", &Vector4::z)
        .def_readwrite("w", &Vector4::w)
        .def("__add__", [](const Vector4& self, const Vector4& other) { return self + other; })
        .def("__sub__", [](const Vector4& self, const Vector4& other) { return self - other; })
        .def("__mul__", [](const Vector4& self, float scalar) { return self * scalar; })
        .def("__rmul__", [](const Vector4& self, float scalar) { return self * scalar; });
}