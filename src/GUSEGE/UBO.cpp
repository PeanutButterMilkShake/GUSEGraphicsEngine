#include <GUSEGE/UBO.h>

UBO::UBO() : uboID(0), bindingPoint(0), bufferSize(0) {}

UBO::UBO(GLsizeiptr size, GLuint binding)
{
    bufferSize = size;
    bindingPoint = binding;

    glGenBuffers(1, &uboID);
    glBindBuffer(GL_UNIFORM_BUFFER, uboID);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, uboID);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::UpdateData(const void *data, GLsizeiptr size, GLintptr offset)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << __LINE__ << " " << __FILE__ << " OpenGL error: " << err << std::endl;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, uboID);
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << __LINE__ << " " << __FILE__ << " OpenGL error: " << err << std::endl;
    }
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UBO::~UBO()
{
    if (glIsBuffer(uboID))
    {
        glDeleteBuffers(1, &uboID);
    }
}
