#include <GUSEGE/ChunkLoader.h>

Shader ChunkLoader::sharedShader;

void ChunkLoader::Update(float deltaTime, GLFWwindow* window)
{
    // 1) Remove out‑of‑range chunks
    chunks.erase(
        std::remove_if(chunks.begin(), chunks.end(),
            [&](const std::unique_ptr<Chunk>& chunkPtr) {
                // chunkPtr is a unique_ptr<Chunk> — dereference to get the Chunk
                float dist = (chunkPtr->position - position).magnitude();
                float limit = renderDistance * Chunk::chunkDimensions.x;
                return dist > limit;
            }),
        chunks.end()
    );

    // 2) Add missing chunks
    for (int x = -renderDistance; x <= renderDistance; ++x)
    for (int y = -renderDistance; y <= renderDistance; ++y)
    for (int z = -renderDistance; z <= renderDistance; ++z)
    {
        Vector3 offset(x, y, z);
        if (offset.magnitude() > renderDistance) continue;

        Vector3 chunkPos = position + offset * Chunk::chunkDimensions.x/10;

        // check existence
        bool exists = false;
        for (const auto& chunkPtr : chunks) {
            if (chunkPtr->position == chunkPos) {
                exists = true;
                break;
            }
        }
        if (exists) continue;

        // create new chunk
        auto newChunk = std::make_unique<Chunk>();
        newChunk->position = chunkPos;
        newChunk->shaderProgram = &sharedShader;  // if you’re sharing a shader
        newChunk->Start();

        chunks.push_back(std::move(newChunk));
    }
}


ChunkLoader::ChunkLoader() { }
ChunkLoader::~ChunkLoader() { }

void ChunkLoader::Start() {
    sharedShader.Load("D:\\GUSEProjects\\GraphicsEngine\\assets\\Shaders\\Vertex\\shader.vert", "D:\\GUSEProjects\\GraphicsEngine\\assets\\Shaders\\Fragment\\shader.frag");
}

void ChunkLoader::FixedUpdate(float fixedDeltaTime, GLFWwindow* window) { }