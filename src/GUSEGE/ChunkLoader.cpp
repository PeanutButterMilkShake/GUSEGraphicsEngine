#include <GUSEGE/ChunkLoader.h>

void ChunkLoader::Update(float deltaTime, GLFWwindow* window)
{
    for(Chunk chunk : chunks)
    {
        if((chunk.position - position).magnitude() > renderDistance * Chunk::chunkDimensions.x)
        {
            chunk.~Chunk();
        }
    }
}