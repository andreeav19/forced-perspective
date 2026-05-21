#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D depthTexture;
uniform sampler2D blurTexture;

void main() {
    float depth = texture(depthTexture, TexCoords).r;
    float focus = 0.5f;

    float blurFactor = abs(depth - focus);
    blurFactor = smoothstep(0.0f, 0.3f, blurFactor);

    vec3 sharp = texture(screenTexture, TexCoords).rgb;
    vec3 blurred = texture(blurTexture, TexCoords).rgb;

    vec3 final = mix(sharp, blurred, blurFactor);

    FragColor = vec4(sharp, 1.0f);
}