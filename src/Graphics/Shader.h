#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
public:
    std::string vertexFilePath;
    std::string fragmentFilePath;
    GLuint ID; // Program ID

    Shader(const char* vertexPath, const char* fragmentPath);
    virtual ~Shader() = default;

    static GLuint CompileShader(GLenum type, const char *source); // No instance data
    static std::string LoadShaderSource(const char *path);        // No instance data

    void Use() const { glUseProgram(ID); } // Common convenience method
};
