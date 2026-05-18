#include "../headers/GameObject.h"

GameObject::GameObject(Model model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
    : model(model), position(position), scale(scale), rotation(rotation) {}

void GameObject::AddRigidBody(btCollisionShape *collision_shape, const float mass)
{
    auto transform = glm::mat4(1.0f);
    transform = translate(transform, position);
    transform = rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    transform = rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transform = rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));

    const auto rb = new RigidBody(transform, collision_shape, mass);
    rigid_body.reset(rb);
}

void GameObject::Render()
{
    if (rigid_body == nullptr || rigid_body->GetMass() == 0) {
        auto transform = glm::mat4(1.0f);
        transform = translate(transform, position);
        transform = glm::scale(transform, scale);
        transform = rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        transform = rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        transform = rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));

        model.Render(transform);
    }
    else {
        glm::mat4 rb_transform = rigid_body->GetCurrentTransform();
        // rb_transform = glm::scale(rb_transform, scale);

        rb_transform[0] = glm::vec4(glm::vec3(rb_transform[0]) * scale.x, 0.0f);
        rb_transform[1] = glm::vec4(glm::vec3(rb_transform[1]) * scale.x, 0.0f);
        rb_transform[2] = glm::vec4(glm::vec3(rb_transform[2]) * scale.x, 0.0f);

        model.Render(rb_transform);

    }
}
