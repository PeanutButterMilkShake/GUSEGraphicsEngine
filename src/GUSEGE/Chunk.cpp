#include <GUSEGE/Chunk.h>

struct FaceTransform {
    Vector3 blockToCheck;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 offset;
};

std::vector<FaceTransform> faceTransforms = {
    { Vector3( 0,  1,  0), glm::vec3(0, 0, 0),     0.0f,  glm::vec3(0, 1, 0) },    
    { Vector3( 1,  0,  0), glm::vec3(0, 0, 1),    -90.0f,  glm::vec3(1.0f, 0, 0) },    
    { Vector3(-1,  0,  0), glm::vec3(0, 0, 1),   90.0f,  glm::vec3(-1.0f, 0, 0) },   
    { Vector3( 0,  0,  1), glm::vec3(1, 0, 0),   90.0f,  glm::vec3(0, 0, 1.0f) },    
    { Vector3( 0,  0, -1), glm::vec3(1, 0, 0),    -90.0f,  glm::vec3(0, 0, -1.0f) },   
    { Vector3( 0, -1,  0), glm::vec3(1, 0, 0),   180.0f,  glm::vec3(0, 0, 0) }    
};

int GetIndex(int x, int y, int z, const Vector3 dim) {
    return x * dim.y * dim.z + y * dim.z + z;
}

VoxelData Chunk::GetBlockAt(Vector3 position)
{
    if (position.x < 0 || position.y < 0 || position.z < 0 ||
        position.x >= chunkDimensions.x ||
        position.y >= chunkDimensions.y ||
        position.z >= chunkDimensions.z)
    {
        return VoxelData(); // returns default = "air"
    }

    return VoxelRegistry::GetBlockFromRegistry(
        chunkData[GetIndex(position.x, position.y, position.z, chunkDimensions)]
    );
}

bool Chunk::IsAirAt(Vector3 position)
{
    return Chunk::GetBlockAt(position).name == "air";
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
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int x = 0; x < chunkDimensions.x; x++)
    {
        for (int z = 0; z < chunkDimensions.z; z++)
        {
            float scale = 0.01f; // Adjust this to control terrain frequency
            float noise = glm::perlin(glm::vec2(x + position.x, z + position.z) * scale);

            noise = (noise + 1.0f) / 2.0f;
            int height = static_cast<int>(std::round(noise * (chunkDimensions.y - 1)));

            for (int y = 0; y <= height; ++y) {
                chunkData[GetIndex(x, y, z, chunkDimensions)] = "stone";
            }
        }
    }
}

std::vector<Vertex> OffsetVoxelVerts(const std::vector<Vertex>& voxelVerts, Vector3 position, const FaceTransform& transform, Vector3 color) 
{
    std::vector<Vertex> result;
    result.reserve(voxelVerts.size());

    glm::mat4 model = glm::mat4(1.0f);
    
    // Apply rotation if needed
    if (transform.rotationAngle != 0.0f) {
        model = glm::rotate(model, glm::radians(transform.rotationAngle), transform.rotationAxis);
    }

    // Extract rotation matrix for normals (upper-left 3x3 of model)
    glm::mat3 normalMatrix = glm::mat3(model);

    for (const auto& v : voxelVerts) {
        Vertex offsetVert = v;

        // Transform position (correct order: model * vec4)
        offsetVert.position = model * glm::vec4(glm::vec3(v.position), 1.0f);

        // Translate to chunk position + offset, scaled down if needed
        offsetVert.position += glm::vec4(((glm::vec3)position + transform.offset) / 10.0f, 0.0f);

        // Transform normal vector by rotation matrix only
        offsetVert.normal = normalMatrix * glm::vec3(v.normal);

        // Make sure normal is normalized
        offsetVert.normal = offsetVert.normal.Normalized();

        offsetVert.color = color;

        result.push_back(offsetVert);
    }

    return result;
}


void Chunk::GenerateMesh()
{
    std::vector<Vertex> planeVerts;
    std::vector<unsigned int> planeIndicies;
    ReadMeshFile("D:\\GUSEProjects\\GraphicsEngine\\assets\\Models\\Plane.obj", &planeVerts, &planeIndicies);

    unsigned int vertexOffset = 0;
    for (int x = 0; x < chunkDimensions.x; x++)
    {
        for (int z = 0; z < chunkDimensions.z; z++)
        {
            for (int y = 0; y < chunkDimensions.y; ++y)
            {
                if(chunkData[GetIndex(x, y, z, chunkDimensions)] == "")
                    continue;

                Vector3 voxelColor = VoxelRegistry::GetBlockFromRegistry(chunkData[GetIndex(x, y, z, chunkDimensions)]).color;
                Vector3 voxelPosition = Vector3(x, y, z);

                for (const auto& face : faceTransforms)
                {
                    Vector3 neighborPos = voxelPosition + face.blockToCheck;
                    if (neighborPos.x < 0 || neighborPos.x >= chunkDimensions.x ||
                        neighborPos.y < 0 || neighborPos.y >= chunkDimensions.y ||
                        neighborPos.z < 0 || neighborPos.z >= chunkDimensions.z) {
                        continue;
                    }

                    if (IsAirAt(neighborPos)) {
                        auto offsetVerts = OffsetVoxelVerts(
                            planeVerts,
                            Vector3(x, y, z),
                            face,
                            voxelColor
                        );

                        vertices.insert(vertices.end(), offsetVerts.begin(), offsetVerts.end());

                        for (unsigned int i = 0; i < planeIndicies.size(); ++i) {
                            indices.push_back(planeIndicies[i] + vertexOffset);
                        }

                        vertexOffset += static_cast<unsigned int>(planeVerts.size());
                    }
                }

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

    VoxelData currentVoxel = VoxelData();
    bool editingVoxel = false;
    for (int i = 0; i < testVoxelData.size(); i++)
    {
        std::string word = testVoxelData[i];

        if (word == "[Voxel]")
        {
            if(editingVoxel)
                VoxelRegistry::AddToRegistry(currentVoxel);

            currentVoxel = VoxelData("air", Vector3());
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