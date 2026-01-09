#include "frame.hpp"
#include "application.hpp"
#include "component.hpp"
#include "renderer.hpp"
#include <GLFW/glfw3.h>

void resizeCallback_(GLFWwindow* window, int width, int height)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame)
    {
        frame->viewportSize =
            Vector2(static_cast<float>(width), static_cast<float>(height));
        if (!frame->resizeCallback.is_none())
            frame->resizeCallback(frame, Vector2(static_cast<float>(width),
                                                 static_cast<float>(height)));
    }
}

void viewportSizeCallback_(GLFWwindow* window, int width, int height)
{
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame)
    {
        frame->viewportSize.x = width;
        frame->viewportSize.y = height;
    }
}

void contentScaleCallback_(GLFWwindow* window, float xscale, float yscale)
{
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame)
    {
        frame->contentScale.x = xscale;
        frame->contentScale.y = yscale;
    }
}

void closeCallback_(GLFWwindow* window)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame)
    {
        if (!frame->closeCallback.is_none())
            frame->closeCallback(frame);
        frame->destroy();
    }
}

void focusCallback_(GLFWwindow* window, int focused)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->focusCallback.is_none())
        frame->focusCallback(frame, focused != 0);
}

void minimizeCallback_(GLFWwindow* window, int iconified)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->minimizeCallback.is_none())
        frame->minimizeCallback(frame, iconified != 0);
}

void maximizeCallback_(GLFWwindow* window, int maximized)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->maximizeCallback.is_none())
        frame->maximizeCallback(frame, maximized != 0);
}

Frame::Frame(Application* app, const Vector2& size, const std::string& title)
    : app(app), size(size), title(title)
{
    window =
        glfwCreateWindow(static_cast<int>(size.x), static_cast<int>(size.y),
                         title.c_str(), nullptr, app->masterWindow);
    if (!window)
        throw std::runtime_error("Failed to create GLFW window");

    glfwSetWindowUserPointer(window, this);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    this->viewportSize = Vector2(static_cast<float>(w), static_cast<float>(h));

    float xs, ys;
    glfwGetWindowContentScale(window, &xs, &ys);
    this->contentScale = Vector2(xs, ys);

    glfwSetWindowSizeCallback(window, resizeCallback_);
    glfwSetWindowCloseCallback(window, closeCallback_);
    glfwSetWindowContentScaleCallback(window, contentScaleCallback_);
    glfwSetWindowFocusCallback(window, focusCallback_);
    glfwSetWindowIconifyCallback(window, minimizeCallback_);
    glfwSetWindowMaximizeCallback(window, maximizeCallback_);

    app->frames.push_back(this);
}

void Frame::render()
{
    glfwMakeContextCurrent(window);
    Vector4 c = Color::toPipelineColor(bgColor);
    glClearColor(c.x, c.y, c.z, c.w);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Component* component : components)
    {
        component->render(this);
    }

    glfwSwapBuffers(window);
}
void Frame::update() {}

void Frame::destroy() { destroyed = true; }
Frame::~Frame()
{
    if (window)
        glfwDestroyWindow(window);
}
void Frame::setSize(const Vector2& newSize)
{
    glfwSetWindowSize(window, (int)newSize.x, (int)newSize.y);
}
Vector2 Frame::getSize() const { return size; }
void Frame::setTitle(const std::string& newTitle)
{
    title = newTitle;
    glfwSetWindowTitle(window, title.c_str());
}
std::string Frame::getTitle() const { return title; }
void Frame::setBackgroundColor(const Color& color) { bgColor = color; }
Color Frame::getBackgroundColor() const { return bgColor; }
void Frame::addComponent(Component* component)
{
    components.push_back(component);
}
void Frame::removeComponent(Component* component)
{
    auto it = std::find(components.begin(), components.end(), component);
    if (it != components.end())
        components.erase(it);
}

void Frame::setIcon(const Image& image)
{
    GLFWimage icon;
    icon.width = image.getWidth();
    icon.height = image.getHeight();
    int channels = 4;
    std::vector<unsigned char> flippedPixels(icon.width * icon.height *
                                             channels);
    int rowSize = icon.width * channels;
    for (int y = 0; y < icon.height; ++y)
    {
        memcpy(&flippedPixels[(icon.height - 1 - y) * rowSize],
               &image.getBytes()[y * rowSize], rowSize);
    }
    icon.pixels = flippedPixels.data();
    glfwSetWindowIcon(window, 1, &icon);
}