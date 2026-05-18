#include "../headers/PhysicsSimulation.h"

PhysicsSimulation::PhysicsSimulation()
{
    collision_configuration = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher = std::make_unique<btCollisionDispatcher>(collision_configuration.get());
    broad_phase_interface = std::make_unique<btDbvtBroadphase>();
    solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    dynamics_world = std::make_unique<btDiscreteDynamicsWorld>(
        dispatcher.get(),
        broad_phase_interface.get(),
        solver.get(),
        collision_configuration.get()
    );

    dynamics_world->setGravity(btVector3(0.0f, -9.8f, 0.0f));
}

void PhysicsSimulation::AddRigidBody(const RigidBody* rigid_body) const
{
    dynamics_world->addRigidBody(rigid_body->GetRigidBody());
}

void PhysicsSimulation::Update() const
{
    dynamics_world->stepSimulation(TIME_STEP, MAX_SUB_STEPS);
}
