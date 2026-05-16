#include "../headers/Material.h"

Material::Material(glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    : ambience(ambience), diffuse(diffuse), specular(specular), shininess(shininess) {}

Material::Material()
{
    ambience = glm::vec3(1.0f, 0.5f, 0.31f);
    diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    specular = glm::vec3(0.5f, 0.5f, 0.5f);
    shininess = 32;
}
