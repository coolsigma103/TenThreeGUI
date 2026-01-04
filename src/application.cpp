#include "application.hpp"
#include "frame.hpp"
#include <GLFW/glfw3.h>
#include <stb/stb_include.h>
#include <stdexcept>

Application::Application()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    masterWindow = glfwCreateWindow(1, 1, "", nullptr, nullptr);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    if (!masterWindow)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create master GLFW window");
    }
    glfwMakeContextCurrent(masterWindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}
Application::~Application()
{
    glfwDestroyWindow(masterWindow);
    glfwTerminate();
}
void Application::run()
{
    while (!shouldClose)
    {
        std::queue<Frame*> closedFrames;
        glfwPollEvents();

        for (Frame* frame : frames)
        {
            if (frame->destroyed)
            {
                closedFrames.push(frame);
            }
            else
            {
                glfwMakeContextCurrent(frame->window);
                glfwSwapBuffers(frame->window);
            }
        }
        while (!closedFrames.empty())
        {
            Frame* frame = closedFrames.front();
            closedFrames.pop();
            auto it = std::find(frames.begin(), frames.end(), frame);
            if (it != frames.end())
                frames.erase(it);
            delete frame;
        }
        if (frames.empty())
            shouldClose = true;
    }
}