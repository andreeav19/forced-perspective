#include "../headers/Light.h"

Light::Light()
{
    position = glm::vec3(0.0f);
    ambience = glm::vec3(0.2f);
    diffuse = glm::vec3(0.5f);
    specular = glm::vec3(1.0f);
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

Light::Light(glm::vec3 position, glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular,
        float constant, float linear, float quadratic)
    : position(position), ambience(ambience), diffuse(diffuse), specular(specular)
    , constant(constant), linear(linear), quadratic(quadratic) {}