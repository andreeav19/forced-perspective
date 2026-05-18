#pragma once

#include <glm/glm.hpp>

#include "Model.h"
#include "RigidBody.h"

class GameObject {
    Model model;
    std::unique_ptr<RigidBody> rigid_body{};
    glm::mat4 transform;

public:
    GameObject(Model model, glm::mat4 transform);
    ~GameObject() = default;

    void AddRigidBody(btCollisionShape* collision_shape, float mass=0.0f);
    void Render();
};
