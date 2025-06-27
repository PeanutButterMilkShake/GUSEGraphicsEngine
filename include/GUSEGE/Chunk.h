#ifndef CHUNK_H
#define CHUNK_H

#include "Utility.h"
#include "Shader.h"
#include "Camera.h"
#include "Scene.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <glm/gtc/noise.hpp>
#include <GUSEGE/Object.h>
#include <GUSEGE/VoxelData.h>

using namespace Utility;

class Chunk : public Object
{
public:
    // File paths

    const char *vertexShaderPath;
    const char *fragmentShaderPath;

    // OpenGL objects

    Shader shaderProgram;
    VAO vao;
    VBO vbo;
    EBO ebo;

    // Mesh data
    Vector3 chunkDimensions;
    std::vector<std::string> chunkData;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    virtual void Start();
    virtual void Update(float deltaTime, GLFWwindow* window);
    virtual void FixedUpdate(float fixedDeltaTime, GLFWwindow* window);

    void GenerateChunk();
    void GenerateMesh();
    void ApplyShaders();

    Chunk();
    ~Chunk();

private:
    bool isMeshApplied = false;
};

#endif