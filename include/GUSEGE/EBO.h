#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
    GLuint ID;
    std::vector<unsigned int> indices;

    void Bind();
    void Unbind();
    void SetData(const std::vector<unsigned int> &indices);

    EBO();
    ~EBO();

private:
};

#endif