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

uniform float amplitudes[4];
uniform float frequencies[4];
uniform float phases[4];
uniform float time;

// Specify the output of the vertex stage
out vec2 uv;
out vec3 normal;
out vec3 vertCoordinates;
out float totalWaveHeight;

float waveHeight(int waveIdx, float u) {
    float amp = amplitudes[waveIdx];
    float freq = frequencies[waveIdx];
    float phase = phases[waveIdx];
    float t = time;
    float angle = 2 * M_PI * freq * u + t + phase;
    return amp * sin(angle);

}

float waveDU(int waveIdx, float u) {
    float amp = amplitudes[waveIdx];
    float freq = frequencies[waveIdx];
    float phase = phases[waveIdx];
    float t = time;
    float angle = 2 * M_PI * freq * u + t + phase;
    return amp * cos(angle) * (2 * M_PI * freq);
}

void main()
{

    vec3 curPos = vertCoordinates_in;

    float waveSum = 0.0f;
    float waveDerivativeSumU = 0.0f;
    for(int i = 1; i < 4; i++) {
        waveSum += waveHeight(i, uv_in.x);
        waveDerivativeSumU += waveDU(i, uv_in.x);
    }

    normal = normTransform  * normalize(vec3(-waveDerivativeSumU, 0.0f, 1.0f));

    totalWaveHeight = waveSum;
    curPos.z += waveSum;

    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = projectionTransform * modelViewTransform * vec4(curPos, 1.0);
    vertCoordinates = vec3(modelViewTransform * vec4(vertCoordinates_in, 1.0));
    uv = uv_in;

}
