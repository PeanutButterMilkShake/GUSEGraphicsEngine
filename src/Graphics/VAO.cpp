#include "VAO.h"

VAO::VAO(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
    this->vertices = vertices;
    this->indices = indices;

    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
}

void VAO::Bind() const
{
    glBindVertexArray(ID);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}

void VAO::AddUniformMat4Buffer(GLuint programID, std::string name, auto data) const
{
    GLuint modelLoc = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(data));
}

template <typename T>
void VAO::AddVertexBuffer(GLuint bufferID, GLuint bindingPoint, const std::vector<T>& data, GLsizei stride) const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

    // bind buffer to vertex binding point
    glBindVertexBuffer(bindingPoint, bufferID, 0, stride);
}

void VAO::AddIndexBuffer(GLuint bufferID, auto data) const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
}