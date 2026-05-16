#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texSampler;

uniform float ambienceStrength;
uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 viewPos;
float specularStrength = 10.5f;

void main() {
    vec3 ambient = ambienceStrength * lightColor;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);

    float diffuseValue = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = diffuseValue * lightColor;

    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
    vec3 specular = specularStrength * specularValue * lightColor;

    vec3 baseColor = texture(texSampler, TexCoord).xyz;
    vec3 finalColor = (ambient + diffuse + specular) * baseColor;
    FragColor = vec4(finalColor, 1.0f);
}