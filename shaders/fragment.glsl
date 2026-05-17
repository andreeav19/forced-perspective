#version 330 core

#define LIGHTS_NUMBER 4

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

struct Light {
    vec3 position;

    vec3 ambience;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform vec3 viewPos;

uniform Light lights[LIGHTS_NUMBER];
uniform Material material;

vec3 CalculateLight(Light light, vec3 normal, vec3 viewDirection) {
    vec3 baseDiffuseColor = texture(material.diffuse, TexCoord).rgb;
    vec3 baseSpecular = texture(material.specular, TexCoord).rgb;

    vec3 ambience = baseDiffuseColor * light.ambience;
    vec3 lightDirection = normalize(light.position - FragPos);

    float diffuseValue = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = baseDiffuseColor * diffuseValue * light.diffuse;

    vec3 reflectDirection = reflect(-lightDirection, normal);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = baseSpecular * specularValue * light.specular;

    float dist = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    return (ambience + diffuse + specular) * attenuation;
}

void main() {
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f);
    for (int i = 0; i < LIGHTS_NUMBER; i++)
        result += CalculateLight(lights[i], normal, viewDirection);

    FragColor = vec4(result, 1.0f);
}