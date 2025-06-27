#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene;

class Camera : public Object
{
public:
    float fov = 1280/720;        // Field of view in degrees
    float aspectRatio = 1.0f; // Aspect ratio of the viewport
    float nearPlane = 0.001f; // Near clipping plane
    float farPlane = 1000.0f; // Far clipping plane

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    virtual void Start();
    virtual void Update(float deltaTime, GLFWwindow* window);
    virtual void FixedUpdate(float fixedDeltaTime, GLFWwindow* window);

    Camera();
    ~Camera();

private:
};

#endif