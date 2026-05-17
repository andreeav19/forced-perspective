#pragma once

#include <vector>

#include "Model.h"

class Scene {
    std::vector<Model> models;

public:
    Scene() = default;
    ~Scene() = default;

    void init();
    void render();
};
