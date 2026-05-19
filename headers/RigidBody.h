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
    [[nodiscard]] float GetMass() const { return mass; }
    [[nodiscard]] glm::mat4 GetCurrentTransform() const;

    void SetActive(bool is_kinematic) const;
    void SetTransform(glm::vec3 position, glm::quat rotation) const;

    static btCollisionShape* CreatePropsShape();
    static btCollisionShape* CreateRoomShape();
    static btCollisionShape* CreateBackpackShape();
};
