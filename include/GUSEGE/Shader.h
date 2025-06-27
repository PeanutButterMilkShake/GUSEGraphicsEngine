#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GUSEGE/Utility.h>

using namespace Utility;

class Shader
{
public:
    Shader();
    ~Shader();

    void Load(const char *vertexPath, const char *fragmentPath);
    GLuint GetID() const;

private:
    GLuint ID;
};

#endif