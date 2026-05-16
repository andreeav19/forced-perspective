#include "../headers/Light.h"

Light::Light()
{
    position = glm::vec3(0.0f);
    ambience = glm::vec3(0.2f);
    diffuse = glm::vec3(0.5f);
    specular = glm::vec3(1.0f);
}

Light::Light(glm::vec3 position, glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular)
: position(position), ambience(ambience), diffuse(diffuse), specular(specular) {}