#pragma once

#include <glm/glm.hpp>

class Light {
    static float ambience;
    glm::vec3 position;
    glm::vec3 color;

public:
    Light();
    Light(glm::vec3 position, glm::vec3 color);
    ~Light() = default;

    static float GetAmbience() { return ambience; }
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetColor() const { return color; }
};
