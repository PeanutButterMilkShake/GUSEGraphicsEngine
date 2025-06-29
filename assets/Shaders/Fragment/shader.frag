#version 460 core

in vec3 FragPos;
in vec3 Normal;
in vec3 VoxelColor;

out vec4 FragColor;

const vec3 lightDir = normalize(vec3(-0.3, -1.0, -0.5));
const vec3 lightColor = vec3(1.0, 1.0, 1.0);

// Ambient light intensity (e.g., 20%)
const float ambientStrength = 0.05;

void main()
{
    vec3 norm = normalize(Normal);

    // Ambient component
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse component
    float diff = max(dot(norm, -lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * VoxelColor;

    FragColor = vec4(result, 1.0);
}
