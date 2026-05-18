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

    is_debug_enabled = false;
}

void PhysicsSimulation::AddRigidBody(const RigidBody* rigid_body) const
{
    if (rigid_body == nullptr) return;
    dynamics_world->addRigidBody(rigid_body->GetRigidBody());
}

void PhysicsSimulation::Update() const
{
    dynamics_world->stepSimulation(TIME_STEP, MAX_SUB_STEPS);
}

void PhysicsSimulation::EnableDebugDraw(const bool is_enabled)
{
    if (is_enabled && debug_drawer == nullptr) {
        debug_drawer.reset(new DebugDrawer());
        dynamics_world->setDebugDrawer(debug_drawer.get());
    }

    is_debug_enabled = is_enabled;
}

void PhysicsSimulation::Render(const glm::mat4 &view, const glm::mat4 &projection) const
{
    if (!is_debug_enabled) return;
    dynamics_world->debugDrawWorld();
    debug_drawer->Render(view, projection);
}
