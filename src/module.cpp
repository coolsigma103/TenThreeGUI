#include "application.hpp"
#include "assets/color.hpp"
#include "assets/image.hpp"
#include "component.hpp"
#include "components/panel.hpp"
#include "frame.hpp"
#include "maths/matrix.hpp"
#include "maths/vector.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(TTGUI, m)
{
    py::module_ maths = m.def_submodule("maths");
    py::module_ assets = m.def_submodule("assets");
    PY_MATRIX_HPP(maths);
    PY_VECTOR_HPP(maths);
    PY_COLOR_HPP(assets);
    PY_IMAGE_HPP(assets);
    PY_APPLICATION_HPP(m);
    PY_COMPONENT_HPP(m);
    PY_FRAME_HPP(m);
    PY_PANEL_HPP(m);
}