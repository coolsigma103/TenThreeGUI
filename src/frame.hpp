#pragma once
#include "maths/vector.hpp"
#include "module.hpp"
#include <memory>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

class Frame
{
    Vector2 size;
    std::string title;
    GLFWwindow* window = nullptr;
    Application* app = nullptr;
    bool destroyed = false;

    py::object resizeCallback;
    py::object closeCallback;
    py::object focusCallback;
    py::object minimizeCallback;
    py::object maximizeCallback;

    friend void resizeCallback_(GLFWwindow* window, int width, int height);
    friend void closeCallback_(GLFWwindow* window);
    friend void focusCallback_(GLFWwindow* window, int focused);
    friend void minimizeCallback_(GLFWwindow* window, int iconified);
    friend void maximizeCallback_(GLFWwindow* window, int maximized);

    friend class Application;

public:
    Frame(Application* app, const Vector2& size = Vector2(110, 103),
          const std::string& title = "TenThreeGUI Frame");
    ~Frame();
    void destroy();
    void setSize(const Vector2& newSize);
    Vector2 getSize() const;
    void setTitle(const std::string& newTitle);
    std::string getTitle() const;
    void setResizeCallback(py::object callback) { resizeCallback = callback; }
    void setCloseCallback(py::object callback) { closeCallback = callback; }
    void setFocusCallback(py::object callback) { focusCallback = callback; }
    void setMinimizeCallback(py::object callback) { minimizeCallback = callback; }
    void setMaximizeCallback(py::object callback) { maximizeCallback = callback; }
};

inline void PY_FRAME_HPP(pybind11::module_& m)
{
    pybind11::class_<Frame>(m, "Frame")
        .def(pybind11::init<Application*, const Vector2&, const std::string&>(), py::arg("app"),
             py::arg("size") = Vector2(110, 103), py::arg("title") = "TenThreeGUI Frame")
        .def("setSize", &Frame::setSize)
        .def("getSize", &Frame::getSize)
        .def("setTitle", &Frame::setTitle)
        .def("getTitle", &Frame::getTitle)
        .def("destroy", &Frame::destroy)
        .def("setResizeCallback", &Frame::setResizeCallback)
        .def("setCloseCallback", &Frame::setCloseCallback)
        .def("setFocusCallback", &Frame::setFocusCallback)
        .def("setMinimizeCallback", &Frame::setMinimizeCallback)
        .def("setMaximizeCallback", &Frame::setMaximizeCallback);
}