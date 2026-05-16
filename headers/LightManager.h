#pragma once

#include <memory>
#include <vector>

#include "Light.h"
#include "Shader.h"

class LightManager {
    std::vector<std::unique_ptr<Light>> lights;

    void SetupLights();
public:
    LightManager();
    ~LightManager() = default;

    void SetUniforms(const Shader* shader) const;
};
