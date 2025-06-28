#include <GUSEGE.h>

int main()
{
    GUSEGE::InitializeEngine();

    Camera camera;
    camera.name = "Camera";
    ChunkLoader chunkLoader;
    chunkLoader.name = "ChunkLoader";
    chunkLoader.renderDistance = 1;

    while (!glfwWindowShouldClose(GUSEGE::GetWindow()))
    {
        GUSEGE::UpdateEngine();
    }

    GUSEGE::CloseEngine();

    return 0;
}
