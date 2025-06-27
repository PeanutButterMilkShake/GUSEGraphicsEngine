#include <GUSEGE/EBO.h>

EBO::EBO()
{
    glGenBuffers(1, &ID);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &ID);
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::SetData(const std::vector<unsigned int> &indices)
{
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    Unbind();
}
