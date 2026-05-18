#pragma once

#include <memory>
#include <vector>

#include <btBulletDynamicsCommon.h>

#include "DebugDrawer.h"
#include "RigidBody.h"
#include "Constants.h"

class PhysicsSimulation {
    std::unique_ptr<DebugDrawer> debug_drawer{};
    std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> broad_phase_interface;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
    std::unique_ptr<btDiscreteDynamicsWorld> dynamics_world;

    bool is_debug_enabled;

public:
    PhysicsSimulation();
    ~PhysicsSimulation() = default;

    void AddRigidBody(const RigidBody* rigid_body) const;
    void Update() const;

    void EnableDebugDraw(bool is_enabled);
    void Render(const glm::mat4 &view, const glm::mat4 &projection) const;
};
