#include <GUSEGE/Chunk.h>

int getIndex(int x, int y, int z, const Vector3 dim) {
    return x * dim.y * dim.z + y * dim.z + z;
}


void Chunk::ApplyShaders()
{
    if (!vertexShaderPath || !fragmentShaderPath)
    {
        std::cerr << "Vertex or Fragment shader path is not set." << std::endl;
        return;
    }

    shaderProgram.Load(vertexShaderPath, fragmentShaderPath);

    glUseProgram(shaderProgram.GetID());
}

void Chunk::GenerateChunk()
{
    for (int x = 0; x < chunkDimensions.x; x++)
    {
        for (int z = 0; z < chunkDimensions.z; z++)
        {
            float scale = 0.05f; // Adjust this to control terrain frequency
            float noise = glm::perlin(glm::vec2(x, z) * scale);

            noise = (noise + 1.0f) / 2.0f;
            int height = static_cast<int>(std::round(noise * (chunkDimensions.y - 1)));

            for (int y = 0; y <= height; ++y) {
                float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                
                if(r > 0.5)
                    chunkData[getIndex(x,y,z, chunkDimensions)] = "red";
                else
                    chunkData[getIndex(x,y,z, chunkDimensions)] = "blue";
            }
        }
    }
}

std::vector<Vertex> OffsetVoxelVerts(std::vector<Vertex> voxelVerts, Vector3 position, Vector3 color)
{
    std::vector<Vertex> result;
    result.reserve(voxelVerts.size());

    for (const auto& v : voxelVerts)
    {
        Vertex offsetVert = v;
        offsetVert.position += position/10;
        offsetVert.color = color;
        result.push_back(offsetVert);
    }

    return result;
}


void Chunk::GenerateMesh()
{
    std::vector<Vertex> voxelVerts;
    std::vector<unsigned int> voxelIndicies;
    ReadMeshFile("D:\\GUSEProjects\\GraphicsEngine\\assets\\Models\\Cube.obj", &voxelVerts, &voxelIndicies);

    unsigned int vertexOffset = 0;
    for (int x = 0; x < chunkDimensions.x; x++)
    {
        for (int z = 0; z < chunkDimensions.z; z++)
        {
            for (int y = 0; y < chunkDimensions.y; ++y)
            {
                if(chunkData[getIndex(x, y, z, chunkDimensions)] == "")
                    continue;

                Vector3 voxelColor = VoxelRegistry::GetBlockFromRegistry(chunkData[getIndex(x, y, z, chunkDimensions)]).color;

                std::vector<Vertex> offsetVerts = OffsetVoxelVerts(voxelVerts, Vector3(x,y,z), voxelColor);
                vertices.insert(vertices.end(), offsetVerts.begin(), offsetVerts.end());

                for (unsigned int i = 0; i < voxelIndicies.size(); ++i) {
                    indices.push_back(voxelIndicies[i] + vertexOffset);
                }


                vertexOffset += static_cast<unsigned int>(voxelVerts.size());

            }
        }
    }

    vao.Bind();

    vbo.SetData(vertices);

    ebo.SetData(indices);

    vbo.Bind();
    ebo.Bind();

    vao.SetupAttributes();
    vao.Unbind();

    ApplyShaders();

    std::cout << "Generated chunk mesh: "
          << vertices.size() << " vertices, "
          << indices.size() << " indices" << std::endl;

}


void Chunk::Update(float deltaTime, GLFWwindow* window)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    glUseProgram(shaderProgram.GetID());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

    GLuint modelLoc = glGetUniformLocation(shaderProgram.GetID(), "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram.GetID(), "view");
    GLuint projLoc = glGetUniformLocation(shaderProgram.GetID(), "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Scene::mainCamera->GetViewMatrix()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(Scene::mainCamera->GetProjectionMatrix()));

    // Render the mesh
    vao.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    vao.Unbind();
}

void Chunk::Start()
{
    std::vector<std::string> testVoxelData = splitStringIntoWords(LoadFileSource("D:\\GUSEProjects\\GraphicsEngine\\assets\\Blocks\\TestVoxels.txt"));

    VoxelData currentVoxel;
    bool editingVoxel = false;
    for (int i = 0; i < testVoxelData.size(); i++)
    {
        std::string word = testVoxelData[i];

        if (word == "[Voxel]")
        {
            if(editingVoxel)
                VoxelRegistry::AddToRegistry(currentVoxel);

            currentVoxel = VoxelData{};
            editingVoxel = true;
        }
        if(word == "name")
        {
            currentVoxel.name = testVoxelData[i + 1];
        }
        else if(word == "color")
        {
            currentVoxel.color = Vector3(std::stof(testVoxelData[i + 1]), std::stof(testVoxelData[i + 2]), std::stof(testVoxelData[i + 3]));
        }
    }

    if(editingVoxel)
        VoxelRegistry::AddToRegistry(currentVoxel);

    GenerateChunk();
    GenerateMesh();
}

void Chunk::FixedUpdate(float fixedDeltaTime, GLFWwindow* window)
{
}

Chunk::Chunk()
{
    chunkDimensions = Vector3(64, 64, 64);
    chunkData.resize(chunkDimensions.x * chunkDimensions.y * chunkDimensions.z);
}

Chunk::~Chunk()
{
}