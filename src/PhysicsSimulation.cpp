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
    return MultipleRayCasts(from, to, hit, camera);
    // return UseRayCastPerspective(from, to, hit);
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

bool PhysicsSimulation::MultipleRayCasts(const btVector3 from, const btVector3 to, glm::vec3& hit, const Camera* camera)
{
    float min_distance = RAY_CAST_LENGTH + 1;
    bool has_hit = false;

    for (int i = 0; i < RAY_GRID_LENGTH; i++) {
        for (int j = 0; j < RAY_GRID_LENGTH; j++) {
            // offset
            const float offset_x = (i - RAY_GRID_LENGTH / 2) * RAY_DISTANCE;
            const float offset_y = (j - RAY_GRID_LENGTH / 2) * RAY_DISTANCE;
            const glm::vec3 offset = camera->GetRight() * offset_x + camera->GetUp() * offset_y;

            btVector3 ray_from(from.x() + offset.x, from.y() + offset.y, from.z() + offset.z);
            btVector3 ray_to  (to.x()   + offset.x, to.y()   + offset.y, to.z()   + offset.z);

            // cast first ray
            btCollisionWorld::ClosestRayResultCallback result(ray_from, ray_to);
            result.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
            result.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;

            result.m_collisionFilterMask = Interactive;
            dynamics_world->rayTest(ray_from, ray_to, result);

            // cast second ray
            if (result.hasHit()) {
                rays.insert({ray_from, ray_to});
                if (glm::vec3 ray_hit; UseRayCastPerspective(ray_from, ray_to, ray_hit)) {
                    const float ray_length = distance(glm::vec3(ray_from.x(), ray_from.y(), ray_from.z()), ray_hit);
                    if (min_distance > ray_length)
                        min_distance = ray_length;
                    has_hit = true;
                }
            }
        }
    }

    // center ray
    glm::vec3 cam_origin = camera->GetPosition();
    glm::vec3 cam_front = camera->GetFront();
    hit = cam_origin + cam_front * min_distance;

    return has_hit;
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

void PhysicsSimulation::Render(const glm::mat4 &view, const glm::mat4 &projection)
{
    if (!is_debug_enabled) return;
    dynamics_world->debugDrawWorld();
    debug_drawer->Render(view, projection);

    for (const auto [from, to] : rays) {
        debug_drawer->drawLine(from, to, btVector3(0.537f, 0.878f, 1));
    }
    rays.clear();
}
