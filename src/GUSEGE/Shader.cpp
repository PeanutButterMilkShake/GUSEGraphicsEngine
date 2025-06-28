#include <GUSEGE/Shader.h>

void Shader::Load(const char *vertexPath, const char *fragmentPath)
{
    // Load vertex and fragment source
    std::string vertSrcStr = LoadFileSource(vertexPath);
    std::string fragSrcStr = LoadFileSource(fragmentPath);
    const char *vertSrc = vertSrcStr.c_str();
    const char *fragSrc = fragSrcStr.c_str();
    
    // Create and compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);
    if (!CheckShaderCompile(vertexShader, "Vertex"))
        return;

    // Create and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);
    if (!CheckShaderCompile(fragmentShader, "Fragment"))
        return;

    // Link shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    if (!CheckProgramLink(shaderProgram))
        return;

    // Set program ID
    ID = shaderProgram;

    // Delete shaders as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::GetID() const
{
    return ID;
}

Shader::Shader()
{
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}