// frame.cpp
#include "frame.hpp"
#include "application.hpp"
#include "component.hpp"

// ---- GLFW Callbacks ----
void resizeCallback_(GLFWwindow* window, int width, int height)
{
    py::gil_scoped_acquire acquire;
    Frame* frame = static_cast<Frame*>(glfwGetWindowUserPointer(window));
    if (frame && !frame->resizeCallback.is_none())
    {

        frame->resizeCallback(frame, Vector2(static_cast<float>(width),
                                             static_cast<float>(height)));
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
    : size(size), title(title), bgColor(255.0f, 255.0f, 255.0f, 1.0), app(app),
      resizeCallback(py::none()), closeCallback(py::none()),
      focusCallback(py::none()), minimizeCallback(py::none()),
      maximizeCallback(py::none())
{
    window =
        glfwCreateWindow(static_cast<int>(size.x), static_cast<int>(size.y),
                         title.c_str(), nullptr, app->masterWindow);
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

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
        glfwSetWindowSize(static_cast<GLFWwindow*>(window),
                          static_cast<int>(size.x), static_cast<int>(size.y));
}
Vector2 Frame::getSize() const { return size; }

void Frame::setTitle(const std::string& newTitle)
{
    title = newTitle;
    if (window)
        glfwSetWindowTitle(window, title.c_str());
}
std::string Frame::getTitle() const { return title; }

void Frame::setBackgroundColor(const Color& color)
{
    bgColor = color;
    Vector4 realColor = Color::toPipelineColor(color);
    glfwMakeContextCurrent(window);
    glClearColor(realColor.x, realColor.y, realColor.z, realColor.w);
}
Color Frame::getBackgroundColor() const { return bgColor; }

void Frame::update() {}
void Frame::render()
{
    glfwMakeContextCurrent(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Component* component : components)
    {
        component->render(this);
    }

    glfwSwapBuffers(window);
}

void Frame::setIcon(const Image& image)
{
    GLFWimage icon;
    icon.width = image.getWidth();
    icon.height = image.getHeight();

    // Create a temporary buffer to hold the flipped pixels
    // Assuming 4 channels (RGBA)
    int channels = 4;
    std::vector<unsigned char> flippedPixels(icon.width * icon.height *
                                             channels);

    int rowSize = icon.width * channels;

    for (int y = 0; y < icon.height; ++y)
    {
        // Copy rows from the bottom of the source to the top of the destination
        // Source row index: y
        // Destination row index: (height - 1 - y)
        memcpy(&flippedPixels[(icon.height - 1 - y) * rowSize],
               &image.getBytes()[y * rowSize], rowSize);
    }

    icon.pixels = flippedPixels.data();
    glfwSetWindowIcon(window, 1, &icon);
}

void Frame::addComponent(Component* component)
{
    components.push_back(component);
}
void Frame::removeComponent(Component* component)
{
    components.erase(
        std::remove(components.begin(), components.end(), component),
        components.end());
}