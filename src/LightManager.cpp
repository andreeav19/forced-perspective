#include "../headers/LightManager.h"

LightManager::LightManager()
{
    SetupLights();
}

void LightManager::SetupLights()
{
    // const auto light = std::make_unique<Light>(
    // glm::vec3(1.2f, 1.0f, 2.0f),
    // glm::vec3(1)
    // );

    lights.push_back(std::make_unique<Light>(
    glm::vec3(1.2f, 1.0f, 2.0f),
    glm::vec3(1)
    ));
}

void LightManager::SetUniforms(const Shader *shader) const
{
    // temp
    shader->SetUniformAmbienceStrength(lights.front()->GetAmbience());
    shader->SetUniformLightPosition(lights.front()->GetPosition());
    shader->SetUniformLightColor(lights.front()->GetColor());
}
