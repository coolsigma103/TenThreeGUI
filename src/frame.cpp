// frame.cpp
#include "frame.hpp"
#include "application.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

// ---- GLFW Callbacks ----
void resizeCallback_(GLFWwindow* window, int width, int height)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->resizeCallback.is_none())
    {

        frame->resizeCallback(frame,
                              Vector2(static_cast<float>(width), static_cast<float>(height)));
    }
}

void closeCallback_(GLFWwindow* window)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (!frame)
        return;

    if (!frame->closeCallback.is_none())
    {

        try
        {
            frame->closeCallback(frame);
        }
        catch (py::error_already_set& e)
        {
            py::print("Exception in closeCallback:", e.what());
        }
    }

    frame->destroy();
}

void focusCallback_(GLFWwindow* window, int focused)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->focusCallback.is_none())
    {

        frame->focusCallback(frame, focused != 0);
    }
}

void minimizeCallback_(GLFWwindow* window, int iconified)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->minimizeCallback.is_none())
    {

        frame->minimizeCallback(frame, iconified != 0);
    }
}

void maximizeCallback_(GLFWwindow* window, int maximized)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->maximizeCallback.is_none())
    {

        frame->maximizeCallback(frame, maximized != 0);
    }
}

// ---- Frame methods ----
Frame::Frame(Application* app, const Vector2& size, const std::string& title)
    : size(size), title(title), app(app), resizeCallback(py::none()), closeCallback(py::none()),
      focusCallback(py::none()), minimizeCallback(py::none()), maximizeCallback(py::none())
{
    window = glfwCreateWindow(static_cast<int>(size.x), static_cast<int>(size.y), title.c_str(),
                              nullptr, app->masterWindow);
    if (!window)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }
    app->frames.push_back(this);
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, resizeCallback_);
    glfwSetWindowCloseCallback(window, closeCallback_);
    glfwSetWindowFocusCallback(window, focusCallback_);
    glfwSetWindowIconifyCallback(window, minimizeCallback_);
    glfwSetWindowMaximizeCallback(window, maximizeCallback_);
}

Frame::~Frame() { destroy(); }

void Frame::destroy()
{
    if (!destroyed && window)
    {
        glfwDestroyWindow(static_cast<GLFWwindow*>(window));
        window = nullptr;
        destroyed = true;
    }
}

void Frame::setSize(const Vector2& newSize)
{
    size = newSize;
    if (window)
        glfwSetWindowSize(static_cast<GLFWwindow*>(window), static_cast<int>(size.x),
                          static_cast<int>(size.y));
}

Vector2 Frame::getSize() const { return size; }

void Frame::setTitle(const std::string& newTitle)
{
    title = newTitle;
    if (window)
        glfwSetWindowTitle(window, title.c_str());
}

std::string Frame::getTitle() const { return title; }
