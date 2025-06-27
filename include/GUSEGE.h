#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GUSEGE/Camera.h>
#include <GUSEGE/Scene.h>
#include <GUSEGE/Utility.h>
#include <GUSEGE/Object.h>
#include <chrono>
#include <GUSEGE/UBO.h>
#include <GUSEGE/Shader.h>
#include <GUSEGE/Chunk.h>

#ifndef ImGuiDockNodeFlags_NoTabBar
#define ImGuiDockNodeFlags_NoTabBar (1 << 9) // Usually bit 9, but check your imgui.h if different
#endif

class GUSEGE
{
private:
    static GLFWwindow *window;
    static unsigned int SCR_WIDTH;
    static unsigned int SCR_HEIGHT;

    static float fps;
    static float renderTime;
    static std::chrono::high_resolution_clock::time_point lastFrameTime;
    static int frameCount;
    static std::chrono::high_resolution_clock::time_point lastFPSTime;
    static bool sceneInit;

public:
    static float deltaTime;

    static GLFWwindow *GetWindow() { return window; }
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };

    
    static int InitializeOpenGL()
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW.\n";
            return -1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GUSEGE", NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window.\n";
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD.\n";
            return -1;
        }

        glViewport(0, 0, 1280, 720);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        return 0;
    }

    static void InitializeEngine()
    {
        if (InitializeOpenGL() != 0)
        {
            std::cerr << "Failed to initialize OpenGL.\n";
            return;
        }
    }

    static void UpdateEngine()
    {
        if(!sceneInit)
        {
            Scene::Init();
            sceneInit = true;
        }

        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
        lastFrameTime = currentTime;

        float elapsed = std::chrono::duration<float>(currentTime - lastFPSTime).count();
        if (elapsed >= 1.0f)
        {
            fps = frameCount;
            renderTime = 1000.0f / static_cast<float>(fps);
            frameCount = 0;
            lastFPSTime = currentTime;
        }

        glClearColor(0.05f, 0.06f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Scene Update (always runs)
        Scene::Update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    static void CloseEngine()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GUSEGE();
    ~GUSEGE();
};