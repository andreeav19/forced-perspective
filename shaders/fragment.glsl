#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

struct Light {
    vec3 position;

    vec3 ambience;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambience;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform sampler2D texSampler;
uniform vec3 viewPos;

uniform Light light;
uniform Material material;

void main() {
    vec3 ambience = material.ambience * light.ambience;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);

    float diffuseValue = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = material.diffuse * diffuseValue * light.diffuse;

    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = material.specular * specularValue * light.specular;

    vec3 baseColor = texture(texSampler, TexCoord).xyz;
    vec3 finalColor = (ambience + diffuse + specular) * baseColor;
    FragColor = vec4(finalColor, 1.0f);
}