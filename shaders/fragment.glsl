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
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform vec3 viewPos;

uniform Light light;
uniform Material material;

void main() {
    vec3 baseDiffuseColor = texture(material.diffuse, TexCoord).rgb;
    vec3 baseSpecular = texture(material.specular, TexCoord).rgb;

    vec3 ambience = baseDiffuseColor * light.ambience;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);

    float diffuseValue = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = baseDiffuseColor * diffuseValue * light.diffuse;

    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = baseSpecular * specularValue * light.specular;

    vec3 finalColor = ambience + diffuse + specular;
    FragColor = vec4(finalColor, 1.0f);
}