#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "Utility.h"

class VAO
{
public:
    GLuint ID;

    void Bind();
    void Unbind();
    void SetupAttributes();

    VAO();
    ~VAO();

private:
};

#endif