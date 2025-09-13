#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) : vertexFilePath(vertexPath), fragmentFilePath(fragmentPath)
{
    std::string vertexSource   = LoadShaderSource(vertexPath);
    std::string fragmentSource = LoadShaderSource(fragmentPath);

    GLuint vertexShader   = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check for linking errors
    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(ID, 512, nullptr, log);
        std::cerr << "Shader program linking error:\n" << log << std::endl;
    }

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string Shader::LoadShaderSource(const char* path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::CompileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compilation error (" 
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") 
                  << "):\n" << log << std::endl;
    }

    return shader;
}