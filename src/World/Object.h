#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Object {
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f); // Euler angles in degrees
    glm::vec3 scale = glm::vec3(1.0f);

    Object() = default;
    virtual ~Object() = default;

    glm::mat4 GetModelMatrix() const;

    virtual void Update(float deltaTime) {}
};
