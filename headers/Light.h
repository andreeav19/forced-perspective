#pragma once

#include <glm/glm.hpp>

class Light {
    glm::vec3 position;
    glm::vec3 ambience;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    Light();
    Light(glm::vec3 position, glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular);
    ~Light() = default;

    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetAmbience() const { return ambience; }
    glm::vec3 GetDiffuse() const { return diffuse; }
    glm::vec3 GetSpecular() const { return specular; }
};
