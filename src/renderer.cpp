#include "renderer.hpp"

Renderer::Renderer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float rect[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    unsigned int indices[] = {0, 1, 2, 2, 3, 0};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    defaultVertexShader =
        Program::createShader(defaultVertexShaderSource, GL_VERTEX_SHADER);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteShader(defaultVertexShader);
}

void Renderer::draw(Vector2 size, Vector2 position, Vector2 viewportSize,
                    Vector2 contentScale, Program* program)
{
    glViewport(0, 0, (GLsizei)viewportSize.x, (GLsizei)viewportSize.y);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(program->id);

    float sw = size.x * contentScale.x;
    float sh = size.y * contentScale.y;
    float px = position.x * contentScale.x;
    float py = position.y * contentScale.y;

    Matrix3 model = Translation(px, py) * Scaling(sw, sh);
    glUniformMatrix3fv(glGetUniformLocation(program->id, "model"), 1, GL_FALSE,
                       model.data);

    float w = viewportSize.x;
    float h = viewportSize.y;
    float proj[] = {2.0f / w, 0.0f,  0.0f, 0.0f, -2.0f / h,
                    0.0f,     -1.0f, 1.0f, 1.0f};
    glUniformMatrix3fv(glGetUniformLocation(program->id, "projection"), 1,
                       GL_FALSE, proj);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

GLuint Renderer::Program::createShader(const char* source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    return shader;
}

void Renderer::Program::attachShader(GLuint shader)
{
    glAttachShader(id, shader);
}

void Renderer::Program::link()
{
    glLinkProgram(id);
    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
}