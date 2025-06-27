#include <GUSEGE/VAO.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

// Setup attribute pointers once after binding VAO and VBO
void VAO::SetupAttributes()
{
    Bind(); // Bind VAO
    // Assumes VBO is already bound here!
    glEnableVertexAttribArray(0); // aPos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1); // aNormal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(Vector3)));

    glEnableVertexAttribArray(2); // aColor
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(Vector3)*2));
    Unbind(); // Unbind VAO
}
