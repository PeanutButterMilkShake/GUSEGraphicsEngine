#version 460 core

in vec4 voxelColor;
out vec4 FragColor;

void main() {
    vec3 result = vec3(1.0);

    FragColor = voxelColor;
}
    