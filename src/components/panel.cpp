#include "panel.hpp"
#include "application.hpp"
#include "frame.hpp"
#include "renderer.hpp"

Panel::Panel()
{
    position = Vector2(0.0f, 0.0f);
    size = Vector2(100.0f, 100.0f);
    color = Color(255, 255, 255, 1);
}
Panel::~Panel() {}

void Panel::render(Frame* frame)
{
    Renderer* renderer = frame->getApplication()->getRenderer();
    if (renderer->programs.find("panel") == renderer->programs.end())
    {
        renderer->programs.emplace("panel", Renderer::Program());
        frame->getApplication()->bindMasterWindow();
        GLuint fs = Renderer::Program::createShader(panelFragmentShaderSource,
                                                    GL_FRAGMENT_SHADER);
        renderer->programs.at("panel").attachShader(
            renderer->defaultVertexShader);
        renderer->programs.at("panel").attachShader(fs);
        renderer->programs.at("panel").link();
        glDeleteShader(fs);
    }

    glfwMakeContextCurrent(frame->getWindow());
    GLuint pid = renderer->programs.at("panel").id;
    glUseProgram(pid);
    Vector4 rc = Color::toPipelineColor(color);
    glUniform4f(glGetUniformLocation(pid, "panelColor"), rc.x, rc.y, rc.z,
                rc.w);

    renderer->draw(size, position, frame->getViewportSize(),
                   frame->getContentScale(), &renderer->programs.at("panel"));
}