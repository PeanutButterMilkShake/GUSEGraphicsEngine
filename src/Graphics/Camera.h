#ifndef CAMERA_H
#define CAMERA_H

#include <Object.h>

class Camera : public Object
{
public:
    float fov = 45.0f;
    float aspectRatio = 800.0f / 600.0f;
    float nearPlane = 0.01f;
    float farPlane = 1000.0f;

    Camera() = default;
    virtual ~Camera() = default;

    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
private:


};

#endif