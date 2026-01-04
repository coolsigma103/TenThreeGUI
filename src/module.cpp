#include "module.hpp"
#include "application.hpp"
#include "component.hpp"
#include "frame.hpp"
#include "maths/matrix.hpp"
#include "maths/vector.hpp"
#include "renderer.hpp"

PYBIND11_MODULE(TTGUI, m)
{
    py::module_ maths = m.def_submodule("maths");
    PY_MATRIX_HPP(maths);
    PY_VECTOR_HPP(maths);
    PY_APPLICATION_HPP(m);
    PY_FRAME_HPP(m);
}