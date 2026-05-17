#include "../headers/LightManager.h"

LightManager::LightManager()
{
    SetupLights();
}

void LightManager::SetupLights()
{
    for (int i = 0; i < LIGHTS_NUMBER; i++)
        lights.push_back(std::make_unique<Light>());

    // temp
    lights[0]->SetPosition(glm::vec3( 0.7f,  0.2f,  2.0f));
    lights[1]->SetPosition(glm::vec3( 2.3f, -3.3f, -4.0f));
    lights[2]->SetPosition(glm::vec3( -4.0f,  2.0f, -12.0f));
    lights[3]->SetPosition(glm::vec3( 0.0f,  0.0f, -3.0f));
}

void LightManager::SetUniform(const Shader *shader, const Light *light, int index) const
{
    shader->SetUniformLight(
        index,
        light->GetPosition(),
        light->GetAmbience(),
        light->GetDiffuse(),
        light->GetSpecular(),
        light->GetConstant(),
        light->GetLinear(),
        light->GetQuadratic()
    );
}

void LightManager::SetUniforms(const Shader *shader) const
{
    for (int i = 0; i < LIGHTS_NUMBER; i++) {
        SetUniform(shader, lights[i].get(), i);
    }
}
