#include "../headers/PhysicsSimulation.h"

void PhysicsSimulation::UseRayCastInteractive(const Camera *camera) const
{
    btVector3 from, to;
    CalculateRayCastPoints(camera, from, to);
    UseRayCastInteractive(from, to);
}

bool PhysicsSimulation::UseRayCastPerspective(const Camera *camera, glm::vec3& hit)
{
    btVector3 from, to;
    CalculateRayCastPoints(camera, from, to);
    return UseRayCastPerspective(from, to, hit);
}

void PhysicsSimulation::CalculateRayCastPoints(const Camera *camera, btVector3 &from, btVector3 &to)
{
    const auto position = camera->GetPosition();
    const auto front = camera->GetFront();

    from = btVector3(position.x, position.y, position.z);
    to = btVector3(
        position.x + front.x * RAY_CAST_LENGTH,
        position.y + front.y * RAY_CAST_LENGTH,
        position.z + front.z * RAY_CAST_LENGTH
    );
}

bool PhysicsSimulation::UseRayCastPerspective(const btVector3 from, const btVector3 to, glm::vec3 &hit)
{
    btCollisionWorld::ClosestRayResultCallback result(from, to);
    result.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
    result.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;

    result.m_collisionFilterMask = Default;

    dynamics_world->rayTest(from, to, result);
    if (result.hasHit()) {
        const btVector3 bt_hit = result.m_hitPointWorld;
        hit = glm::vec3(bt_hit.x(), bt_hit.y(), bt_hit.z());
        return true;
    }

    return false;
}

void PhysicsSimulation::UseRayCastInteractive(const btVector3 from, const btVector3 to) const
{
    btCollisionWorld::AllHitsRayResultCallback results(from, to);
    results.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
    results.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;

    results.m_collisionFilterMask = Interactive;

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
    dynamics_world->addRigidBody(
        rigid_body->GetRigidBody(),
        rigid_body->GetCollisionGroup(),
        Default | Interactive);
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
