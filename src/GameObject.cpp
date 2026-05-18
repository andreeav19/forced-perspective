#include "../headers/GameObject.h"

GameObject::GameObject(Model model, glm::mat4 transform): model(model), transform(transform) {}

void GameObject::AddRigidBody(btCollisionShape *collision_shape, const float mass)
{
    const auto rb = new RigidBody(transform, collision_shape, mass);
    rigid_body.reset(rb);
}

void GameObject::Render()
{
    model.Render(transform);
}
