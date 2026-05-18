#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class RigidBody {
    std::unique_ptr<btRigidBody> rigid_body;
    std::unique_ptr<btCollisionShape> collision_shape;
    std::unique_ptr<btDefaultMotionState> motion_state;
    btScalar mass;

public:
    explicit RigidBody(glm::mat4 initial_transform, btCollisionShape* collision_shape, float body_mass=0.0f);
    ~RigidBody() = default;

    [[nodiscard]] btRigidBody* GetRigidBody() const { return rigid_body.get(); }
    [[nodiscard]] btCollisionShape* GetCollisionShape() const { return collision_shape.get(); }
    [[nodiscard]] btDefaultMotionState* GetMotionState() const { return motion_state.get(); }

    // TODO: add helper methods for creating model shapes
};
