#include <iostream>
#include <vector>
#include <GUSEGE/Chunk.h>
#include <GUSEGE/Object.h>

#ifndef CHUNK_LOADER_H
#define CHUNK_LOADER_H

class ChunkLoader: Object{
public:
    int renderDistance;
    std::vector<Chunk> chunks;

    virtual void Start();
    virtual void Update(float deltaTime, GLFWwindow* window);
    virtual void FixedUpdate(float fixedDeltaTime, GLFWwindow* window);
};

#endif