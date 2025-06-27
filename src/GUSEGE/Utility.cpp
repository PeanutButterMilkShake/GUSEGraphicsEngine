#include <GUSEGE/Utility.h>

namespace Utility
{

    void ReadMeshFile(const std::string &filePath, std::vector<Vertex> *vertices, std::vector<unsigned int> *indices)
    {
        std::ifstream meshFile(filePath);
        if (!meshFile.is_open())
        {
            std::cerr << "Failed to open mesh file: " << filePath << std::endl;
            return;
        }

        std::vector<Vector3> tempPositions;
        std::vector<Vector3> tempNormals;
        std::unordered_map<std::string, unsigned int> uniqueVertexMap;

        std::string line;
        while (std::getline(meshFile, line))
        {
            std::istringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v")
            {
                Vector3 pos;
                ss >> pos.x >> pos.y >> pos.z;
                tempPositions.push_back(pos);
            }
            else if (prefix == "vn")
            {
                Vector3 normal;
                ss >> normal.x >> normal.y >> normal.z;
                tempNormals.push_back(normal);
            }
            else if (prefix == "f")
            {
                std::string token;
                for (int i = 0; i < 3; ++i)
                {
                    ss >> token;

                    // Expected format: v//vn or v/vt/vn
                    size_t firstSlash = token.find('/');
                    size_t secondSlash = token.find('/', firstSlash + 1);

                    std::string key = token; // key for deduplication

                    // Check if this vertex/normal combo is already added
                    if (uniqueVertexMap.count(key) == 0)
                    {
                        unsigned int vIndex = std::stoi(token.substr(0, firstSlash)) - 1;
                        unsigned int vnIndex = std::stoi(token.substr(secondSlash + 1)) - 1;

                        Vertex vertex;
                        vertex.position = tempPositions[vIndex]/10;
                        vertex.normal = tempNormals[vnIndex];

                        vertices->push_back(vertex);
                        unsigned int newIndex = static_cast<unsigned int>(vertices->size()) - 1;
                        uniqueVertexMap[key] = newIndex;
                        indices->push_back(newIndex);
                    }
                    else
                    {
                        indices->push_back(uniqueVertexMap[key]);
                    }
                }
            }
        }

        meshFile.close();
    }

    bool CheckProgramLink(GLuint program)
    {
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cerr << "Program Linking Failed:\n"
                      << infoLog << std::endl;
            return false;
        }
        return true;
    }

    bool CheckShaderCompile(GLuint shader, const std::string &type)
    {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << type << " Shader Compilation Failed:\n"
                      << infoLog << std::endl;
            return false;
        }
        return true;
    }

    const std::string LoadFileSource(const std::string &filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    std::vector<std::string> splitStringIntoWords(const std::string& text) {
        std::istringstream stream(text);
        std::vector<std::string> words;
        std::string word;

        while (stream >> word) {
            words.push_back(word);
        }
        return words;
    }

} // namespace Utility
