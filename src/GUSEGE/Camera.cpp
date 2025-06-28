#include <GUSEGE/Camera.h>
#include <GUSEGE/Scene.h>
#include <GLFW/glfw3.h>


glm::mat4 Camera::GetViewMatrix()
{
    glm::vec3 pos = (glm::vec3)position;

    // Convert pitch and yaw (in degrees) to radians
    float pitch = glm::radians(rotation.x);
    float yaw = glm::radians(rotation.y);

    // Calculate forward vector from rotation (yaw and pitch)
    glm::vec3 forward;
    forward.x = cos(pitch) * sin(yaw);
    forward.y = sin(pitch);
    forward.z = -cos(pitch) * cos(yaw);  // Negative Z forward in OpenGL

    glm::vec3 target = pos + glm::normalize(forward);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    return glm::lookAt(pos, target, up);
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
    const float speed = 5.0f; // units per second

    
    // Convert rotation angles (assumed in degrees) to radians
    float pitch = glm::radians(rotation.x);
    float yaw = glm::radians(rotation.y);

    // Calculate forward vector from yaw and pitch
    Vector3 forward;
    forward.x = cos(pitch) * sin(yaw);
    forward.y = sin(pitch);
    forward.z = -cos(pitch) * cos(yaw); // Negative Z is forward in OpenGL

    // Normalize forward just in case
    forward = glm::normalize((glm::vec3)forward);

    // Calculate right vector as cross of forward and world up
    glm::vec3 rightVec = glm::normalize(glm::cross((glm::vec3)forward, glm::vec3(0, 1, 0)));
    Vector3 right(rightVec.x, rightVec.y, rightVec.z);

    // Movement controls
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += forward * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= forward * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * speed * deltaTime;

    // Vertical movement (up/down)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position.y += speed * deltaTime; // Up
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        position.y -= speed * deltaTime; // Down

    // Rotation controls (yaw and pitch)
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotation.y -= speed * 10 * deltaTime; // Yaw left
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotation.y += speed * 10 * deltaTime; // Yaw right
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rotation.x += speed * 10 * deltaTime; // Pitch up
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rotation.x -= speed * 10 * deltaTime; // Pitch down

    // Optional: clamp pitch so you don't flip the camera
    if(rotation.x > 89.0f) rotation.x = 89.0f;
    if(rotation.x < -89.0f) rotation.x = -89.0f;

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