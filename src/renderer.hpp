#pragma once

#include "maths/matrix.hpp"
#include "maths/vector.hpp"
#include <iostream>
#include <unordered_map>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

class Renderer
{
    GLuint VAO;
    GLuint VBO, EBO;

public:
    Renderer();
    ~Renderer();

    struct Program
    {
        GLuint id = 0;
        Program() { id = glCreateProgram(); }
        ~Program()
        {
            if (id)
                glDeleteProgram(id);
        }
        static GLuint createShader(const char* source, GLenum type);
        void attachShader(GLuint shader);
        void link();
    };

    std::unordered_map<std::string, Program> programs;
    void draw(Vector2 size, Vector2 position, Vector2 viewportSize,
              Vector2 contentScale, Program* program);
    GLuint defaultVertexShader;
};

constexpr const char* defaultVertexShaderSource = R"glsl(
#version 330 core 
layout(location = 0) in vec2 aPos;
uniform mat3 model;
uniform mat3 projection;

out vec2 TexCoord;

void main() {
    vec3 pos = projection * model * vec3(aPos, 1.0);
    gl_Position = vec4(pos.xy, 0.0, 1.0);

    TexCoord = aPos + vec2(0.5);
}
)glsl";