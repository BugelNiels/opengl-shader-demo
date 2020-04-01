#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 normalColor_in;
layout (location = 2) in vec2 uv_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelViewTransform;
uniform mat4 projectionTransform;
uniform mat3 normTransform;

// Specify the output of the vertex stage

out vec3 vertCoordinates;
out vec3 normalColor;
out vec2 uv;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = projectionTransform * modelViewTransform * vec4(vertCoordinates_in, 1.0);

    uv = uv_in;
    normalColor = normTransform * normalColor_in;
    vertCoordinates = vec3(modelViewTransform * vec4(vertCoordinates_in, 1.0));
}
