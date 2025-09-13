// main.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader.h>
#include <Camera.h>
#include <VAO.h>

const glm::vec4 clearColor = glm::vec4(0.07f, 0.05f, 0.07f, 1.0f);
const glm::i16vec2 viewPortSize = glm::i16vec2(800, 600);

std::vector<float> planeVerts = {
    -0.5f, 0.0f,  0.5f,
     0.5f, 0.0f,  0.5f,
    -0.5f, 0.0f, -0.5f,
     0.5f, 0.0f, -0.5f
};

std::vector<unsigned int> planeIndices = {
    0, 1, 2,
    1, 3, 2
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera& camera) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position.z -= 0.05f; // Move forward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position.z += 0.05f; // Move backward
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position.x -= 0.05f; // Move left
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position.x += 0.05f; // Move right
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(viewPortSize.x, viewPortSize.y, "OpenGL Plane", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Setup Camera
    Camera camera = Camera();

    // Load and compile shaders
    Shader voxelShader = Shader("D:\\GUSEProjects\\GraphicsEngine\\assets\\Shaders\\Vertex\\shader.vert", "D:\\GUSEProjects\\GraphicsEngine\\assets\\Shaders\\Fragment\\shader.frag");
    GLuint shaderProgram = voxelShader.ID;

    // Setup buffers
    VAO vao = VAO(planeVerts, planeIndices);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    vao.Bind();

    vao.AddVertexBuffer(VBO, 0, planeVerts, sizeof(float) * 3);
    vao.AddIndexBuffer(EBO, planeIndices);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window, camera);

        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        vao.AddUniformMat4Buffer(shaderProgram, "model", glm::mat4(1.0f));
        vao.AddUniformMat4Buffer(shaderProgram, "view", camera.GetViewMatrix());
        vao.AddUniformMat4Buffer(shaderProgram, "projection", camera.GetProjectionMatrix());

        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    vao.~VAO();
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}