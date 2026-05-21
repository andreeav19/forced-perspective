#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D blurTexture;
uniform sampler2D depthTexture;
uniform sampler2D screenTexture;

uniform bool isHeld;

float linearizeDepth(float d) {
    float near = 0.1f;
    float far = 100.0f;
    float z = d * 2.0f - 1.0f;
    return (2.0f * near * far) / (far + near - z * (far - near));
}

void main() {
    float depth = texture(depthTexture, TexCoords).r;
    depth = linearizeDepth(depth);

    float focus = 1.0f;
    float dist_from_focus = abs(depth - focus);

    float blurFactor = smoothstep(0.2f, 3.2f, dist_from_focus);

    vec3 sharp = texture(screenTexture, TexCoords).rgb;
    vec3 blurred = texture(blurTexture, TexCoords).rgb;

    vec3 final = mix(sharp, blurred, blurFactor);

    if (isHeld) FragColor = vec4(sharp, 1.0f);
    else FragColor = vec4(final, 1.0f);
}