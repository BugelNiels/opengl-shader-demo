#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 uv_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
uniform mat3 normTransform;

// Specify the output of the vertex stage
out vec2 uv;
out vec3 normal;
out vec3 vertCoordinates;
out vec3 cameraPos;

void main() {
    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vertCoordinates_in, 1.0);
    normal = normalize(mat3(transpose(inverse(modelTransform))) * normal_in);
    vertCoordinates = vec3(modelTransform * vec4(vertCoordinates_in, 1.0));
    cameraPos = vec3(inverse(viewTransform) * vec4(0, 0, 0, 1));
    uv = uv_in;
}
