#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
out vec4 fColor;

in vec3 uvCoords;

uniform samplerCube cubeMap;

void main() {
//    fColor = texture(cubeMap, uvCoords);
      fColor = vec4(0.4, 0.4, 0.4, 1);
}
