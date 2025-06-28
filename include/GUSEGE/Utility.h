#ifndef UTILITY_H
#define UTILITY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <ostream>

struct LightData
{
    alignas(16) glm::vec3 position;
    float intensity;
    alignas(16) glm::vec3 direction;
    float cutoff;
    alignas(16) glm::vec3 color;
    float outerCutOff;
    alignas(16) glm::vec3 attenuation;
    float lightType;

    // glm vec3 conversion operator
    operator glm::vec3() const
    {
        return glm::vec3(color.x, color.y, color.z);
    }
};

struct Vector3
{
    float x, y, z;

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    Vector3(const glm::vec3& v3) : x(v3.x), y(v3.y), z(v3.z) {}
    Vector3(const glm::vec4& v4) : x(v4.x), y(v4.y), z(v4.z) {}

    // == operator
    bool operator==(const Vector3& other) const
    {
        const float epsilon = 0.00001f;
        return std::fabs(x - other.x) < epsilon &&
               std::fabs(y - other.y) < epsilon &&
               std::fabs(z - other.z) < epsilon;
    }

    std::ostream& print(std::ostream& os) const {
        os << "(" << x << ", " << y << ", " << z << ")";
        return os;
    }

    // Normalize
    Vector3 Normalized() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length > 0.00001f)
        {
            return Vector3(x / length, y / length, z / length);
        }
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Negation
    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    // GLM conversion
    operator glm::vec3() const
    {
        return glm::vec3(x, y, z);
    }

    operator glm::vec4() const
    {
        return glm::vec4(x, y, z, 1.0f);
    }

    // Vector + Vector
    Vector3 operator+(const Vector3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Vector - Vector
    Vector3 operator-(const Vector3& other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Vector * Scalar
    Vector3 operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Vector / Scalar
    Vector3 operator/(float scalar) const
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Compound assignment operators
    Vector3& operator+=(const Vector3& other)
    {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& other)
    {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    Vector3& operator*=(float scalar)
    {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vector3& operator/=(float scalar)
    {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }



    // Common direction vectors
    static Vector3 Right()   { return Vector3(1.0f, 0.0f, 0.0f); }
    static Vector3 Up()      { return Vector3(0.0f, 1.0f, 0.0f); }
    static Vector3 Forward() { return Vector3(0.0f, 0.0f, -1.0f); } // -Z is forward in right-handed OpenGL
};

inline std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    return vec.print(os);
}

struct Vertex
{
    Vector3 position;
    Vector3 normal;
    Vector3 color;

    Vertex(Vector3 position = Vector3(), Vector3 normal = Vector3(), Vector3 color = Vector3()) : position(position), normal(normal), color(color) {}
};

namespace Utility
{
    const std::string LoadFileSource(const std::string &filePath);
    bool CheckShaderCompile(GLuint shader, const std::string &type);
    bool CheckProgramLink(GLuint program);
    void ReadMeshFile(const std::string &filePath, std::vector<Vertex> *vertices, std::vector<unsigned int> *indices);
    std::vector<std::string> splitStringIntoWords(const std::string &text);
}

#endif
