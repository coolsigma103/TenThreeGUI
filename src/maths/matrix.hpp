#pragma once

#include "vector.hpp"
#include <cmath>
#include <pybind11/pybind11.h>
template <int Rows, int Cols> struct Matrix
{
    float data[Rows * Cols];

    Matrix operator+(const Matrix& other) const
    {
        Matrix result;
        for (int i = 0; i < Rows * Cols; i++)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    Matrix operator-(const Matrix& other) const
    {
        Matrix result;
        for (int i = 0; i < Rows * Cols; i++)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    template <int OtherCols>
    Matrix<Rows, OtherCols>
    operator*(const Matrix<Cols, OtherCols>& other) const
    {
        Matrix<Rows, OtherCols> result;
        for (int i = 0; i < Rows; i++)
            for (int j = 0; j < OtherCols; j++)
            {
                result.data[i * OtherCols + j] = 0;
                for (int k = 0; k < Cols; k++)
                    result.data[i * OtherCols + j] +=
                        data[i * Cols + k] * other.data[k * OtherCols + j];
            }
        return result;
    }
};

using Matrix3 = Matrix<3, 3>;

inline Vector3 operator*(const Matrix3& m, const Vector3& v)
{
    return Vector3(m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z,
                   m.data[3] * v.x + m.data[4] * v.y + m.data[5] * v.z,
                   m.data[6] * v.x + m.data[7] * v.y + m.data[8] * v.z);
}
inline Vector3 operator*(const Matrix3& m, const Vector2& v)
{
    return Vector3(m.data[0] * v.x + m.data[1] * v.y + m.data[2],
                   m.data[3] * v.x + m.data[4] * v.y + m.data[5],
                   m.data[6] * v.x + m.data[7] * v.y + m.data[8]);
}

inline Matrix3 Rotation(float angleRadians)
{
    float c = std::cos(angleRadians);
    float s = std::sin(angleRadians);

    Matrix3 m{};
    m.data[0] = c;
    m.data[1] = -s;
    m.data[2] = 0;
    m.data[3] = s;
    m.data[4] = c;
    m.data[5] = 0;
    m.data[6] = 0;
    m.data[7] = 0;
    m.data[8] = 1;
    return m;
}

inline Matrix3 Translation(float tx, float ty)
{
    Matrix3 m{};
    m.data[0] = 1;
    m.data[1] = 0;
    m.data[2] = tx;
    m.data[3] = 0;
    m.data[4] = 1;
    m.data[5] = ty;
    m.data[6] = 0;
    m.data[7] = 0;
    m.data[8] = 1;
    return m;
}

inline Matrix3 Scaling(float sx, float sy)
{
    Matrix3 m{};
    m.data[0] = sx;
    m.data[1] = 0;
    m.data[2] = 0;
    m.data[3] = 0;
    m.data[4] = sy;
    m.data[5] = 0;
    m.data[6] = 0;
    m.data[7] = 0;
    m.data[8] = 1;
    return m;
}

inline void PY_MATRIX_HPP(pybind11::module_& m)
{
    pybind11::class_<Matrix3>(m, "Matrix3")
        .def(pybind11::init<>())
        .def("__add__", &Matrix3::operator+)
        .def("__sub__", &Matrix3::operator-)
        .def("__mul__",
             [](const Matrix3& a, const Matrix3& b) { return a * b; })
        .def("__mul__",
             [](const Matrix3& m, const Vector3& v) { return m * v; })
        .def("__mul__",
             [](const Matrix3& m, const Vector2& v) { return m * v; });
}