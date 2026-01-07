#pragma once

#include <cstring>
#include <pybind11/pybind11.h>
#include <stdexcept>
#include <string>
#include <vector>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "assets/color.hpp"
#include "assets/image.hpp"
#include "maths/vector.hpp"

class Application;
class Component;

class Frame
{
    Vector2 size;
    std::string title;
    Color bgColor;

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

    void update();
    void render();

    std::vector<Component*> components;

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

    void setBackgroundColor(const Color& color);
    Color getBackgroundColor() const;

    void setIcon(const Image& icon);

    void setResizeCallback(py::object callback) { resizeCallback = callback; }
    void setCloseCallback(py::object callback) { closeCallback = callback; }
    void setFocusCallback(py::object callback) { focusCallback = callback; }
    void setMinimizeCallback(py::object callback)
    {
        minimizeCallback = callback;
    }
    void setMaximizeCallback(py::object callback)
    {
        maximizeCallback = callback;
    }

    void addComponent(Component* comp);
    void removeComponent(Component* comp);

    Application* getApplication() { return app; }
    GLFWwindow* getWindow() { return window; }
};

inline void PY_FRAME_HPP(pybind11::module_& m)
{
    pybind11::class_<Frame>(m, "Frame")
        .def(pybind11::init<Application*, const Vector2&, const std::string&>(),
             py::arg("app"), py::arg("size") = Vector2(110, 103),
             py::arg("title") = "TenThreeGUI Frame")
        .def("setSize", &Frame::setSize)
        .def("getSize", &Frame::getSize)
        .def("setTitle", &Frame::setTitle)
        .def("getTitle", &Frame::getTitle)
        .def("setBgColor", &Frame::setBackgroundColor)
        .def("getBgColor", &Frame::getBackgroundColor)
        .def("setIcon", &Frame::setIcon)
        .def("destroy", &Frame::destroy)
        .def("setResizeCallback", &Frame::setResizeCallback)
        .def("setCloseCallback", &Frame::setCloseCallback)
        .def("setFocusCallback", &Frame::setFocusCallback)
        .def("setMinimizeCallback", &Frame::setMinimizeCallback)
        .def("setMaximizeCallback", &Frame::setMaximizeCallback)
        .def("addComponent", &Frame::addComponent)
        .def("removeComponent", &Frame::removeComponent);
}