#pragma once

#include <memory>
#include <vector>

#include "Light.h"
#include "Shader.h"

#include "Constants.h"

class LightManager {
    std::vector<std::unique_ptr<Light>> lights;

    void SetupLights();
    void SetUniform(const Shader* shader, const Light* light, int index) const;
public:
    LightManager();
    ~LightManager() = default;

    void SetUniforms() const;
};
