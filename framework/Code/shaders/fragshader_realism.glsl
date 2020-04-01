#version 330 core

// Define constants
#define M_PI 3.141593

in vec3 vertCoordinates;
in vec3 normal;
in vec2 uv;

in vec3 cameraPos;

uniform bool selected;

uniform sampler2D textureColor;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform samplerCube cubeMap;

uniform mat4 viewTransform;


// The ugliest written shader ever, apologies, but I was running out of time :)

out vec4 fColor;

vec3 sampleRefl(vec3 normal, vec3 viewDir, float factor) {
    // Not a random offset, did not have time to do this, but this simulates roughness quite well
    vec3 norm2 = vec3(normal.x + 0.00123 * factor, normal.y - 0.00124 * factor, normal.z);

    vec3 reflectionDir = normalize(reflect(viewDir, norm2));
    return vec3(texture(cubeMap, reflectionDir));
}


void main()
{
    vec3 N = normal;
    N = N * vec3(texture(normalMap, uv));
    N = normalize(N);

    vec3 viewDir = normalize(vertCoordinates - cameraPos);
    vec3 reflectionDir = normalize(reflect(viewDir, N));

    // Some fresnel like mixing factor
    float nv = dot(-viewDir, N);
    if(nv < 0) {
        nv = 0;
    }
    if(nv > 1) {
        nv = 1;
    }
    float fresnel = 1 - nv;

    // Specular map (kind of)
    vec3 mix = vec3(texture(specularMap, uv));
    float mixFactor = ( (0.3 * mix.r) + (0.59 * mix.g) + (0.11 * mix.b) );

    vec3 reflectColor = vec3(0, 0, 0);
    float roughness = 100 * mixFactor;
    // Introduce roughness by sampling
    for(int i = 0; i < 4; i++) {
        reflectColor += sampleRefl(N, viewDir, i * roughness);
    }
    reflectColor /= 4.0;

    // Main material
    vec3 col1 = reflectColor * (1- mixFactor) * nv;

    // Edges are more reflective
    vec3 col2 = reflectColor * fresnel;
    fColor = vec4(col1 + col2, 1);
}
