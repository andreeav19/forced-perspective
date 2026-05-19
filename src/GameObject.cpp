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

void GameObject::EnableInteractive()
{
    if (rigid_body == nullptr) {
        std::cout << "Warning: cannot enable object interactive without rigid body." << std::endl;
        return;
    }
    // only interactive objects will be returned by ray cast
    rigid_body->GetRigidBody()->setUserPointer(this);
    is_interactive = true;
}

void GameObject::SetPickUpActive(const bool is_active, const Camera *camera)
{
    if (!is_interactive  || is_picked_up == is_active) return;

    is_picked_up = is_active;
    rigid_body->SetActive(is_active);

    pickup_offset = distance(camera->GetPosition(), position);
}

void GameObject::UpdateHoldPosition(const Camera *camera) const
{
    if (rigid_body == nullptr || !is_picked_up) return;

    const auto camera_pos = camera->GetPosition();
    const auto camera_front = camera->GetFront();

    const glm::vec3 hold_pos = camera_pos + camera_front * pickup_offset;

    const auto m_rotation = glm::inverse(glm::mat4(camera->calculateViewMatrix()));
    const glm::quat q_rotation = quat_cast(m_rotation);

    rigid_body->SetTransform(hold_pos, q_rotation);
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
