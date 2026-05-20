#pragma once

#include <memory>
#include <vector>

#include <btBulletDynamicsCommon.h>
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"

#include "Camera.h"
#include "DebugDrawer.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Constants.h"

class PhysicsSimulation {
    std::unique_ptr<DebugDrawer> debug_drawer{};
    std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> broad_phase_interface;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
    std::unique_ptr<btDiscreteDynamicsWorld> dynamics_world;

    bool is_debug_enabled;
    std::map<btVector3, btVector3> rays;

    static void CalculateRayCastPoints(const Camera* camera, btVector3& from, btVector3& to);
    bool UseRayCastPerspective(btVector3 from, btVector3 to, glm::vec3& hit);
    bool MultipleRayCasts(btVector3 from, btVector3 to, glm::vec3& hit, const Camera *camera);
    void UseRayCastInteractive(btVector3 from, btVector3 to) const;

public:
    PhysicsSimulation();
    ~PhysicsSimulation() = default;

    void AddRigidBody(const RigidBody* rigid_body) const;
    void Update() const;
    void UseRayCastInteractive(const Camera* camera) const;
    bool UseRayCastPerspective(const Camera *camera, glm::vec3& hit);

    void EnableDebugDraw();
    void Render(const glm::mat4 &view, const glm::mat4 &projection);
};
