#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertCoordinates;
in vec3 normal;
in vec3 color;
in vec2 uv;


// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

uniform bool selected;
uniform sampler2D textureColor;

uniform int useDiff;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    // change to texture, texture() did not work on this computer
    vec3 materialColor = vec3(1.0f, 1.0f, 1.0f);
    if(useDiff == 1) {
        materialColor = vec3(texture(textureColor, uv));
    }

    vec3 col = color * materialColor;

    vec3 cameraPos = vec3(0.0f, 0.0f, 0.0f);
    vec3 viewDir = normalize(cameraPos - vertCoordinates);

    if(selected) {
        if(dot(viewDir, normal) < 0.35) {
            col = vec3(1.0, 0.45, 0.0);
        }
    }

    fColor = vec4(col, 1.0) ;
}
