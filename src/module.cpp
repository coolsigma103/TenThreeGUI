#include "module.hpp"
#include "application.hpp"
#include "component.hpp"
#include "frame.hpp"
#include "renderer.hpp"

PYBIND11_MODULE(TTGUI, m) {
  py::class_<Application>(m, "Application")
      .def(py::init<>())
      .def("run", &Application::run);

  py::class_<Frame>(m, "Frame").def(py::init<>());

  py::class_<Component>(m, "Component").def(py::init<>());
}