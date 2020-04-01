#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertCoordinates;
in vec3 normalColor;
in vec2 uv;

uniform bool selected;

uniform mat3 normTransform;
uniform sampler2D normalMap;
uniform int useNorm;
uniform float normalMultiplier;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    vec3 col = vec3(0.5) + normalize(normalColor) * 0.5;
    if(useNorm == 1) {
        col =  col * vec3(texture(normalMap, uv));
        col.z *= normalMultiplier;
        col = normalize(col);
    }


    vec3 cameraPos = vec3(0.0f, 0.0f, 0.0f);
    vec3 viewDir = normalize(cameraPos - vertCoordinates);

    if(selected) {
        if(dot(viewDir, normalColor) < 0.35) {
            col = vec3(1.0, 0.45, 0.0);
        }
    }

    fColor = vec4(col, 1.0);
}
