#include <GUSEGE/VBO.h>

VBO::VBO()
{
    glGenBuffers(1, &ID);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &ID);
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::SetData(std::vector<Vertex> &vertices)
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    Unbind();
}
