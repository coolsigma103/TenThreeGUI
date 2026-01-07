#include "renderer.hpp"

Renderer::Renderer()
{
    glGenVertexArrays(1, &VAO);
    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices),
                 rectangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    defaultVertexShader =
        Program::createShader(defaultVertexShaderSource, GL_VERTEX_SHADER);
}
Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

GLuint Renderer::Program::createShader(const char* source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
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
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void Renderer::draw(Vector2 size, Vector2 position, Program* program)
{
    glBindVertexArray(VAO);
    glUseProgram(program->id);
    Matrix3 model =
        Translation(position.x, position.y) * Scaling(size.x, size.y);
    GLuint modelLoc = glGetUniformLocation(program->id, "model");
    glUniformMatrix3fv(modelLoc, 1, GL_FALSE, model.data);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}