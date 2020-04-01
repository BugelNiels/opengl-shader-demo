#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 uv_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelViewTransform;
uniform mat4 projectionTransform;
uniform mat3 normTransform;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 materialColor;
uniform vec4 lightingConstants;


uniform int useDiff;

// Specify the output of the vertex stage
out vec3 color;
out vec3 normal;
out vec2 uv;
out vec3 vertCoordinates;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = projectionTransform * modelViewTransform * vec4(vertCoordinates_in, 1.0);

    vertCoordinates = vec3(modelViewTransform * vec4(vertCoordinates_in, 1.0));

    vec3 mColor = materialColor;
    if(useDiff == 1) {
        mColor = vec3(1.0, 1.0, 1.0);
    }

    normal = normalize(normTransform * normal_in);

    vec3 ambientI = lightingConstants.x * mColor;

    vec3 lightDir = normalize(lightPos - vertCoordinates);

    vec3 diffuseI = max(0.0f, dot(lightDir, normal)) * lightColor * mColor * lightingConstants.y;

    vec3 cameraPos = vec3(0.0f, 0.0f, 0.0f);
    vec3 viewDir = normalize(cameraPos - vertCoordinates);

    vec3 reflectionDir = normalize(-reflect(lightDir, normal));
    vec3 specularI = pow(max(0.0f, dot(reflectionDir, viewDir)), lightingConstants.w) * lightColor * lightingConstants.z;

    color = ambientI + diffuseI + specularI;
    uv = uv_in;

}
