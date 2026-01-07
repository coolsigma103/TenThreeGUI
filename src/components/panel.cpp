#include "panel.hpp"
#include "application.hpp"
#include "frame.hpp"
#include "renderer.hpp"
#include <GLFW/glfw3.h>

Panel::Panel()
{
    position = Vector2(0.0f, 0.0f);
    size = Vector2(1.0f, 1.0f);
    color = Color(255, 255, 255, 1);
}

Panel::~Panel() {}

void Panel::render(Frame* frame)
{
    glfwMakeContextCurrent(frame->getWindow());

    Renderer* renderer = frame->getApplication()->getRenderer();

    auto it = renderer->shaders.find("panel");

    if (it == renderer->shaders.end())
    {
        frame->getApplication()->bindMasterWindow();
        GLuint fragmentShader = Renderer::Program::createShader(
            panelFragmentShaderSource, GL_FRAGMENT_SHADER);

        Renderer::Program panelProgram;
        panelProgram.attachShader(renderer->defaultVertexShader);
        panelProgram.attachShader(fragmentShader);
        panelProgram.link();

        glDeleteShader(fragmentShader);

        renderer->shaders["panel"] = panelProgram.id;
        it = renderer->shaders.find("panel");
        glfwMakeContextCurrent(frame->getWindow());
    }

    GLuint programID = renderer->shaders.at("panel");
    glUseProgram(programID);
    GLuint colorLoc = glGetUniformLocation(programID, "panelColor");
    Vector4 realColor = Color::toPipelineColor(color);
    glUniform4f(colorLoc, realColor.x, realColor.y, realColor.z, realColor.w);
    renderer->draw(size, position, nullptr);
}