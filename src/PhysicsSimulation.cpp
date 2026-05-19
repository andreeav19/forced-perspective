#include "../headers/PhysicsSimulation.h"

void PhysicsSimulation::UseRayCast(const Camera *camera) const
{
    const auto position = camera->GetPosition();
    const auto front = camera->GetFront();

    const btVector3 from(position.x, position.y, position.z);
    const btVector3 to(
        position.x + front.x * RAY_CAST_LENGTH,
        position.y + front.y * RAY_CAST_LENGTH,
        position.z + front.z * RAY_CAST_LENGTH
    );

    btCollisionWorld::AllHitsRayResultCallback results(from, to);
    results.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
    results.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;

    dynamics_world->rayTest(from, to, results);
    for (int i = 0; i < results.m_collisionObjects.size(); i++) {
        const btCollisionObject* collision_object = results.m_collisionObjects[i];
        const auto game_object = static_cast<GameObject *>(collision_object->getUserPointer());
        if (game_object) game_object->SetHovered(true);
    }
}

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

void PhysicsSimulation::EnableDebugDraw()
{
    is_debug_enabled = !is_debug_enabled;

    if (is_debug_enabled && debug_drawer == nullptr) {
        debug_drawer.reset(new DebugDrawer());
        dynamics_world->setDebugDrawer(debug_drawer.get());
    }
}

void PhysicsSimulation::Render(const glm::mat4 &view, const glm::mat4 &projection) const
{
    if (!is_debug_enabled) return;
    dynamics_world->debugDrawWorld();
    debug_drawer->Render(view, projection);
}
