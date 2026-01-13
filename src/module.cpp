#include "assets/color.hpp"
#include "assets/image.hpp"
#include "maths/matrix.hpp"
#include "maths/vector.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(TTGUI, m)
{
    // maths
    py::module_ maths = m.def_submodule("maths");
    auto matrix3 = py::class_<Matrix3>(maths, "Matrix3");
    auto vector2 = py::class_<Vector2>(maths, "Vector2");
    auto vector3 = py::class_<Vector3>(maths, "Vector3");
    auto vector4 = py::class_<Vector4>(maths, "Vector4");

    // assets
    py::module_ assets = m.def_submodule("assets");
    auto color = py::class_<Color>(assets, "Color");
    auto color3 = py::class_<Color3, Color>(assets, "Color3");
    auto image = py::class_<Image>(assets, "Image");

    PY_MATRIX_HPP(matrix3);
    PY_VECTOR_HPP(vector2, vector3, vector4);

    PY_COLOR_HPP(color, color3);
    PY_IMAGE_HPP(image);
}