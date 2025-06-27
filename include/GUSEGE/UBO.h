#ifndef UBO_H
#define UBO_H

#include "Utility.h"

class UBO
{
private:
    GLuint uboID = 0;
    GLuint bindingPoint = 0;
    GLsizeiptr bufferSize = 0;

public:
    UBO();
    UBO(GLsizeiptr size, GLuint binding);
    ~UBO();
    void UpdateData(const void *data, GLsizeiptr size, GLintptr offset);

    GLuint GetID() const { return uboID; }
};

#endif