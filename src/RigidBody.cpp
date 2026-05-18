#include "../headers/RigidBody.h"

#include <iostream>

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

btCollisionShape * RigidBody::CreatePropsShape()
{
    const auto compound_shape = new btCompoundShape();

    btTransform transform;
    transform.setIdentity();

    btQuaternion rotation;

    // table
    transform.setOrigin(btVector3(0.165f, 0.74f, 0.075f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.44f, 0.02f, 0.95f)));

    transform.setOrigin(btVector3(0.165f, 0.4f, 0.18f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.2f, 0.3f, 0.4f)));

    // chair 1
    transform.setOrigin(btVector3(0.165f, 0.43f, -0.95f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.2f, 0.048f, 0.2f)));

    transform.setOrigin(btVector3(0.31f, 0.23f, -1.12f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    transform.setOrigin(btVector3(0.02f, 0.23f, -1.12f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    transform.setOrigin(btVector3(0.02f, 0.23f, -0.8f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    transform.setOrigin(btVector3(0.31f, 0.23f, -0.8f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    rotation.setEulerZYX(0.0f, 0.0f, btRadians(-15.0f));
    transform.setOrigin(btVector3(0.17f, 0.65f, -1.21f));
    transform.setRotation(rotation);
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.2f, 0.23f, 0.04f)));

    // chair 2
    transform.setIdentity();
    transform.setOrigin(btVector3(0.165f, 0.43f, 1.15f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.2f, 0.048f, 0.2f)));

    transform.setOrigin(btVector3(0.31f, 0.23f, 1.32f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    transform.setOrigin(btVector3(0.02f, 0.23f, 1.32f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    transform.setOrigin(btVector3(0.02f, 0.23f, 1.0f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    transform.setOrigin(btVector3(0.31f, 0.23f, 1.0f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.04f, 0.15f, 0.04f)));

    rotation.setEulerZYX(0.0f, 0.0f, btRadians(15.0f));
    transform.setOrigin(btVector3(0.17f, 0.65f, 1.36f));
    transform.setRotation(rotation);
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.2f, 0.23f, 0.04f)));

    // small table
    transform.setIdentity();
    transform.setOrigin(btVector3(-1.355f, 0.66f, 0.075f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.21f, 0.04f, 0.81f)));

    transform.setOrigin(btVector3(-1.355f, 0.4f, 0.83f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.21f, 0.3f, 0.04f)));

    transform.setOrigin(btVector3(-1.355f, 0.4f, -0.75f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.21f, 0.3f, 0.04f)));

    // vases
    transform.setOrigin(btVector3(0.165f, 0.87f, 0.135f));
    compound_shape->addChildShape(transform, new btCylinderShape(btVector3(0.05f, 0.12f, 0.05f)));

    transform.setOrigin(btVector3(-1.355f, 1.0f, 0.65f));
    compound_shape->addChildShape(transform, new btCylinderShape(btVector3(0.1f, 0.31f, 0.1f)));

    transform.setOrigin(btVector3(-1.355f, 0.97f, 0.4f));
    compound_shape->addChildShape(transform, new btCylinderShape(btVector3(0.1f, 0.28f, 0.1f)));

    return compound_shape;
}

btCollisionShape * RigidBody::CreateRoomShape()
{
    const auto compound_shape = new btCompoundShape();

    btTransform transform;
    transform.setIdentity();

    transform.setOrigin(btVector3(0.0f, -0.3f, 0.0f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(3.2f, 0.1f, 3.2f)));

    transform.setOrigin(btVector3(0.0f, 4.7f, 0.0f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(3.2f, 0.1f, 3.2f)));

    transform.setOrigin(btVector3(3.1f, 2.2f, 0.0f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.1f, 2.5f, 3.0f)));

    transform.setOrigin(btVector3(-3.1f, 2.2f, 0.0f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.1f, 2.5f, 3.0f)));

    transform.setOrigin(btVector3(0.0, 2.2f, 3.1f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(3.0f, 2.5f, 0.1f)));

    transform.setOrigin(btVector3(0.0, 2.2f, -3.1f));
    compound_shape->addChildShape(transform, new btBoxShape(btVector3(3.0f, 2.5f, 0.1f)));

    return compound_shape;
}

btCollisionShape * RigidBody::CreateBackpackShape()
{
    const auto compound_shape = new btCompoundShape();

    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(0.0f, 0.0f, -0.05f));

    compound_shape->addChildShape(transform, new btBoxShape(btVector3(0.18f, 0.17f, 0.05)));

    return compound_shape;
}
