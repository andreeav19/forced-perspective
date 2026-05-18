#pragma once

#include <memory>
#include <vector>

#include <btBulletDynamicsCommon.h>

#include "RigidBody.h"
#include "Constants.h"

class PhysicsSimulation {
    std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> broad_phase_interface;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
    std::unique_ptr<btDiscreteDynamicsWorld> dynamics_world;

public:
    PhysicsSimulation();
    ~PhysicsSimulation() = default;

    void AddRigidBody(const RigidBody* rigid_body) const;
    void Update() const;
};
