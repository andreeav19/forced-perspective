#pragma once

#include <vector>

#include "GameObject.h"
#include "Model.h"
#include "PhysicsSimulation.h"

class ObjectsManager {
    std::vector<Model> models;
    std::vector<std::unique_ptr<GameObject>> game_objects;

    bool is_debug_enabled = false;
    GameObject* held_game_object = nullptr;

public:
    ObjectsManager() = default;
    ~ObjectsManager() = default;

    GameObject* GetHoveredGameObject() const;

    GameObject*& GetHeldGameObject() { return held_game_object; }

    void init(const PhysicsSimulation* physics_simulation);
    void render();
    void update(const Camera* camera) const;
    void update(const Camera* camera, glm::vec3 far_position) const;

    void resetObjectsHovered();
    void clear() const;
};
