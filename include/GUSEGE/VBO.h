#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <vector>
#include "utility.h"

class VBO
{
public:
    GLuint ID;
    std::vector<Vertex> vertices;

    void Bind();
    void Unbind();
    void SetData(std::vector<Vertex> &vertices);

    VBO();
    ~VBO();

private:
};

#endif