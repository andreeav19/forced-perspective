#pragma once

#include <glm/glm.hpp>

#include "Model.h"
#include "RigidBody.h"

class GameObject {
    Model model;
    std::unique_ptr<RigidBody> rigid_body{};
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    bool is_interactive = false;
    bool is_picked_up = false;
    bool is_hovered = false;
    float pickup_offset = 0.0f;

public:
    GameObject(Model model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
    ~GameObject() = default;

    [[nodiscard]] RigidBody* GetRigidBody() const { return rigid_body.get(); }
    [[nodiscard]] bool IsHovered() const { return is_hovered; }

    void SetHovered(const bool new_hovered) { is_hovered = new_hovered; }

    void AddRigidBody(btCollisionShape* collision_shape, float mass=0.0f);
    void EnableInteractive();
    void SetPickUpActive(bool is_active, const Camera* camera);
    void UpdateHoldPosition(const Camera* camera) const;
    void Render();
};
