#pragma once

#include <glm/glm.hpp>

class Light {
    glm::vec3 position;
    glm::vec3 ambience;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant, linear, quadratic;

public:
    Light();
    Light(glm::vec3 position, glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular,
        float constant, float linear, float quadratic);
    ~Light() = default;

    [[nodiscard]] glm::vec3 GetPosition() const { return position; }
    [[nodiscard]] glm::vec3 GetAmbience() const { return ambience; }
    [[nodiscard]] glm::vec3 GetDiffuse() const { return diffuse; }
    [[nodiscard]] glm::vec3 GetSpecular() const { return specular; }
    [[nodiscard]] float GetConstant() const { return constant; }
    [[nodiscard]] float GetLinear() const { return linear; }
    [[nodiscard]] float GetQuadratic() const { return quadratic; }

    void SetPosition(const glm::vec3 new_position) { position = new_position; }
};
