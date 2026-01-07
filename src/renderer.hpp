#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "maths/matrix.hpp"
#include "maths/vector.hpp"
#include <iostream>
#include <unordered_map>
constexpr GLfloat rectangleVertices[] = {
    -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
};
constexpr GLuint rectangleIndices[] = {0, 1, 2, 2, 3, 0};

class Renderer
{
    GLuint VAO;
    GLuint VBO, EBO;

public:
    Renderer();
    ~Renderer();

    std::unordered_map<const char*, GLuint> shaders;

    struct Program
    {
        GLuint id;

        Program() { id = glCreateProgram(); }
        ~Program() { glDeleteProgram(id); }

        static GLuint createShader(const char* source, GLenum type);
        void attachShader(GLuint shader);
        void link();
    };

    void draw(Vector2 size, Vector2 position, Program* program);

    GLuint defaultVertexShader;
};

constexpr const char* defaultVertexShaderSource = R"glsl(

#version 330 core 

layout(location = 0) in vec2 aPos;

uniform mat3 model;

out vec2 TexCoord;

void main()
{
    vec3 pos = model * vec3(aPos, 1.0);

    gl_Position = vec4(pos.xy, 0.0, 1.0);

    TexCoord = aPos + vec2(0.5);
}

)glsl";