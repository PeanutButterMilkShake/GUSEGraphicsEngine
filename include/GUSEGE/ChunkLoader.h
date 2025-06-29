#include <iostream>
#include <vector>
#include <GUSEGE/Chunk.h>
#include <GUSEGE/Object.h>
#include <GUSEGE/Shader.h>

#ifndef CHUNK_LOADER_H
#define CHUNK_LOADER_H

class ChunkLoader : public Object {
public:
    int renderDistance;
    std::vector<std::unique_ptr<Chunk>> chunks;

    static Shader sharedShader;

    ChunkLoader();
    ~ChunkLoader();

    virtual void Start();
    virtual void Update(float deltaTime, GLFWwindow* window);
    virtual void FixedUpdate(float fixedDeltaTime, GLFWwindow* window);
};
#endif