#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertCoordinates;
in vec3 normal;
in vec2 uv;
in float totalWaveHeight;

uniform bool selected;

uniform sampler2D textureColor;
uniform sampler2D specularMap;
uniform sampler2D normalMap;

uniform float specularMultiplier;
uniform float normalMultiplier;

uniform int useDiff;
uniform int useSpec;
uniform int useNorm;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 materialColor;
uniform vec4 lightingConstants;

uniform mat4 modelViewTransform;
uniform mat4 projectionTransform;
uniform mat3 normTransform;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main() {


    vec3 col1 = vec3(0.0f, 0.1f, 1.0f);
    vec3 col2 = vec3(1.0f, 1.0f, 1.0f);
    vec3 color = mix(col1, col2, smoothstep(-0.2f, 0.2f, totalWaveHeight));

    if(useDiff == 1) {
        color = vec3(texture(textureColor, uv));
    }

    vec3 N = normal;
    if(useNorm == 1) {

        N = N * vec3(texture(normalMap, uv));
        N.z *= normalMultiplier;
        N = normalize(N);
    }

    vec3 ambientI = lightingConstants.x * color;

    vec3 lightDir = normalize(lightPos - vertCoordinates);


    vec3 diffuseI = max(0.0f, dot(lightDir, N)) * lightColor * color * lightingConstants.y;

    vec3 cameraPos = vec3(0.0f, 0.0f, 0.0f);
    vec3 viewDir = normalize(cameraPos - vertCoordinates);

    vec3 reflectionDir = normalize(-reflect(lightDir, N));
    vec3 specularI = pow(max(0.0f, dot(reflectionDir, viewDir)), lightingConstants.w) * lightColor * lightingConstants.z;

    vec3 specularComp;
    if(useSpec == 1) {
        specularI = specularI * specularMultiplier * vec3(texture(specularMap, uv));
    }



    vec3 finalColor = ambientI + diffuseI + specularI;

    if(selected) {
        if(dot(viewDir, N) < 0.35) {
            finalColor = vec3(1.0, 0.45, 0.0);
        }
    }

    fColor = vec4(finalColor, 1.0);

}
