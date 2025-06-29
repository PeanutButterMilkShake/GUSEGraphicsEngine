#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;      // world space position
out vec3 Normal;       // normal in world space
out vec3 VoxelColor;   // pass color as vec3

void main()
{
    vec4 worldPosition = model * vec4(aPos, 1.0);
    FragPos = worldPosition.xyz;

    Normal = mat3(transpose(inverse(model))) * aNormal; // transform normal properly
    VoxelColor = aColor;

    gl_Position = projection * view * worldPosition;
}
