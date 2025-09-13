#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

class VAO
{
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    GLuint ID;

    VAO(std::vector<float>& vertices, std::vector<unsigned int>& indices);
    ~VAO();

    void Bind() const;
    void Unbind() const;
    void AddUniformMat4Buffer(GLuint programID, std::string name, auto data) const;
    void AddVertexBuffer(GLuint bufferID, GLuint bindingPoint, const std::vector<T>& data, GLsizei stride) const
    void AddIndexBuffer(GLuint bufferID, auto data) const;
    void BindVertexBuffer(GLuint bufferID, GLuint bindingPoint) const;

private:

};

#endif