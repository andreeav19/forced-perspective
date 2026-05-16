#pragma once

#include <glm/glm.hpp>

class Material {
    glm::vec3 ambience;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

public:
    Material();
    Material(glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular, float shininess);

    [[nodiscard]] glm::vec3 GetAmbience() const { return ambience; }
    [[nodiscard]] glm::vec3 GetDiffuse() const { return diffuse; }
    [[nodiscard]] glm::vec3 GetSpecular() const { return specular; }
    [[nodiscard]] float GetShininess() const { return shininess; }
};