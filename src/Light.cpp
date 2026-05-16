#include "../headers/Light.h"

float Light::ambience = 0.2f;

Light::Light()
{
    position = glm::vec3(0.0f);
    color = glm::vec3(1.0f);
}

Light::Light(glm::vec3 position, glm::vec3 color) : position(position), color(color) {}