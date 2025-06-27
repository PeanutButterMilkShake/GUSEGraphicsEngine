#include <GUSEGE/Camera.h>
#include <GUSEGE/Scene.h>
#include <GLFW/glfw3.h>


glm::mat4 Camera::GetViewMatrix()
{
    glm::vec3 pos = (glm::vec3)position;
    glm::vec3 target = pos + glm::vec3(0.0f, 0.0f, -1.0f);
    return glm::lookAt(pos, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

Camera::Camera()
{
    fov = 40.0f;        // Field of view in degrees
    aspectRatio = 1280.0f/720.0f; // Aspect ratio of the viewport
    nearPlane = 0.001f; // Near clipping plane
    farPlane = 1000.0f; // Far clipping plane
    if (!Scene::mainCamera)
    {
        Scene::mainCamera = this;
    }
}


void Camera::Update(float deltaTime, GLFWwindow* window)
{
    const float speed = 50.0f; // units per second

    
    Vector3 forward = Vector3(0, 0, -1);
    glm::vec3 rightVec = glm::normalize(glm::cross((glm::vec3)forward, glm::vec3(0, 1, 0)));
    Vector3 right(rightVec.x, rightVec.y, rightVec.z);


    // WASD controls
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += forward * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= forward * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position -= Vector3(0,-1,0) * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        position -= Vector3(0,1,0) * speed * deltaTime;
}

void Camera::Start() {}
void Camera::FixedUpdate(float fixedDeltaTime, GLFWwindow* window) {}

Camera::~Camera()
{
    if (Scene::mainCamera == this)
    {
        Scene::mainCamera = nullptr;
    }
}