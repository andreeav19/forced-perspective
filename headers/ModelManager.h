#pragma once

#include <vector>

#include "Model.h"

class ModelManager {
    std::vector<Model> models;

public:
    ModelManager() = default;
    ~ModelManager() = default;

    void init();
    void render();
    void clear() const;
};
