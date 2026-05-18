#pragma once

#include <vector>

#include "GameObject.h"
#include "Model.h"
#include "PhysicsSimulation.h"

class ObjectsManager {
    std::unique_ptr<PhysicsSimulation> physics_simulation;

    std::vector<Model> models;
    std::vector<std::unique_ptr<GameObject>> game_objects;

    bool is_debug_enabled;

public:
    ObjectsManager() = default;
    ~ObjectsManager() = default;

    void init();
    void render(const glm::mat4 &view, const glm::mat4 &projection);
    void update() const;
    void switchDebugRender();
    void clear() const;
};
