#include <GUSEGE.h>

int main()
{
    GUSEGE::InitializeEngine();

    Camera camera;

    Chunk chunk;
    chunk.name = "chunk";
    chunk.vertexShaderPath = "D:\\GUSEProjects\\GraphicsEngine\\assets\\Shaders\\Vertex\\shader.vert";
    chunk.fragmentShaderPath = "D:\\GUSEProjects\\GraphicsEngine\\assets\\Shaders\\Fragment\\shader.frag";
    chunk.position = Vector3();   

    while (!glfwWindowShouldClose(GUSEGE::GetWindow()))
    {
        GUSEGE::UpdateEngine();
    }

    GUSEGE::CloseEngine();

    return 0;
}
