#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CollisionGroup {
    Default = 1,
    Interactive = 2
};

class RigidBody {
    std::unique_ptr<btRigidBody> rigid_body;
    std::unique_ptr<btCollisionShape> collision_shape;
    std::unique_ptr<btDefaultMotionState> motion_state;
    btScalar mass;
    CollisionGroup collision_group = Default;

public:
    explicit RigidBody(glm::mat4 initial_transform, btCollisionShape* collision_shape,
        float body_mass=0.0f, CollisionGroup group=Default);
    ~RigidBody() = default;

    [[nodiscard]] btRigidBody* GetRigidBody() const { return rigid_body.get(); }
    [[nodiscard]] btCollisionShape* GetCollisionShape() const { return collision_shape.get(); }
    [[nodiscard]] btDefaultMotionState* GetMotionState() const { return motion_state.get(); }
    [[nodiscard]] float GetMass() const { return mass; }
    [[nodiscard]] CollisionGroup GetCollisionGroup() const { return collision_group; }
    [[nodiscard]] glm::mat4 GetCurrentTransform() const;

    void SetActive(bool is_active) const;
    void SetTransform(glm::vec3 position, glm::quat rotation) const;

    static btCollisionShape* CreatePropsShape();
    static btCollisionShape* CreateRoomShape();
    static btCollisionShape* CreateBackpackShape();

    [[nodiscard]] float CalculateHalfDimensionZ() const;
};
