#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texSampler;

void main() {
    FragColor = texture(texSampler, TexCoord) * vec4(vertexColor, 1.0);
}