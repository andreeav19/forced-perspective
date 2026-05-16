#include "../headers/LightManager.h"

LightManager::LightManager()
{
    SetupLights();
}

void LightManager::SetupLights()
{
    lights.push_back(std::make_unique<Light>());
}

void LightManager::SetUniforms(const Shader *shader) const
{
    // temp
    shader->SetUniformLight(
    lights.front()->GetPosition(),
        lights.front()->GetAmbience(),
        lights.front()->GetDiffuse(),
        lights.front()->GetSpecular()
    );
}
