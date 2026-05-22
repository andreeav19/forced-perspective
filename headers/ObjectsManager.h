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

    [[nodiscard]] GameObject* GetHoveredGameObject() const;
    GameObject*& GetHeldGameObject() { return held_game_object; }
    [[nodiscard]] bool IsObjectHeld() const { return held_game_object? true : false;}

    void Init(const PhysicsSimulation* physics_simulation);
    void Render();
    void Update(const Camera* camera) const;
    void Update(const Camera* camera, glm::vec3 far_position) const;

    void ResetObjectsHovered();
    void Clear() const;
};
