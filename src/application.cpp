#include "application.hpp"
#include "frame.hpp"

#include "renderer.hpp"

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

    renderer = new Renderer();
}
Application::~Application()
{
    glfwDestroyWindow(masterWindow);
    glfwTerminate();
}
void Application::run()
{
    float waitTime = 1.0f / 60.0f; // 60 FPS
    float lastCheck = glfwGetTime();

    while (!shouldClose)
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastCheck;

        if (deltaTime < waitTime) // if frame is faster than 1/60s, sleep
        {
            // Sleep for remaining time
            float sleepTime = waitTime - deltaTime;
            if (sleepTime > 0.0f)
                std::this_thread::sleep_for(
                    std::chrono::duration<float>(sleepTime));
            currentTime = glfwGetTime(); // recalc after sleep
            deltaTime = currentTime - lastCheck;
        }

        lastCheck = currentTime;

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
                frame->update();
                frame->render();
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

Renderer* Application::getRenderer() { return renderer; }