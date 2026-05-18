#include "../headers/RigidBody.h"

RigidBody::RigidBody(glm::mat4 initial_transform, btCollisionShape* collision_shape, const float mass)
    : collision_shape(collision_shape), mass(mass)
{
    btTransform bt_transform;
    bt_transform.setFromOpenGLMatrix(value_ptr(initial_transform));

    btVector3 local_inertia(0, 0, 0);
    if (mass != 0.0f) // if dynamic
        collision_shape->calculateLocalInertia(mass, local_inertia);

    motion_state = std::make_unique<btDefaultMotionState>(bt_transform);

    btRigidBody::btRigidBodyConstructionInfo rb_info(
        mass, motion_state.get(), this->collision_shape.get(), local_inertia);
    rigid_body = std::make_unique<btRigidBody>(rb_info);
}

glm::mat4 RigidBody::GetCurrentTransform() const
{
    btTransform bt_transform;
    motion_state->getWorldTransform(bt_transform);

    glm::mat4 model;
    bt_transform.getOpenGLMatrix(value_ptr(model));

    return model;
}
