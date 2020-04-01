#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 uv_in;

out vec3 uvCoords;

uniform mat4 modelViewTransform;
uniform mat4 projectionTransform;

void main() {
    uvCoords = vertCoordinates_in;
    mat4 viewTransform = mat4(mat3(modelViewTransform));
    gl_Position = projectionTransform * viewTransform * vec4(vertCoordinates_in, 1.0);
}
