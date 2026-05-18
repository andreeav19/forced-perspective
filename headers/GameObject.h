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

public:
    GameObject(Model model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
    ~GameObject() = default;

    [[nodiscard]] RigidBody* GetRigidBody() const { return rigid_body.get(); }

    void AddRigidBody(btCollisionShape* collision_shape, float mass=0.0f);
    void Render();
};
