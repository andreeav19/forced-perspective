#include "../headers/GameObject.h"

GameObject::GameObject(Model model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
    : model(model), position(position), scale(scale), rotation(rotation),
      original_position(0), original_scale(0) {}

void GameObject::AddRigidBody(btCollisionShape *collision_shape, const float mass, const CollisionGroup collision_group)
{
    auto transform = glm::mat4(1.0f);
    transform = translate(transform, position);
    transform = rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    transform = rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transform = rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));

    const auto rb = new RigidBody(transform, collision_shape, mass, collision_group);
    rigid_body.reset(rb);

    if (collision_group == Interactive) {
        rigid_body->GetRigidBody()->setUserPointer(this);
    }
}

void GameObject::SetPickUpActive(const bool is_active, const Camera *camera)
{
    if (is_picked_up == is_active) return;

    is_picked_up = is_active;
    rigid_body->SetActive(is_active);

    original_position = position;
    original_scale = scale;
    original_bt_scale = rigid_body->GetCollisionShape()->getLocalScaling();
    original_distance = distance(camera->GetPosition(), original_position);

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

void GameObject::ForceScale(const Camera* camera, const glm::vec3 far_position)
{
    const float new_distance = distance(camera->GetPosition(), far_position);
    const glm::vec3 new_scale = original_scale * (new_distance / original_distance);

    const float half_rb_z = rigid_body->CalculateHalfDimensionZ();
    const float offset = half_rb_z * new_scale.z * 1.2f;
    const glm::vec3 new_position = far_position - camera->GetFront() * offset;

    position = new_position;
    scale = new_scale;

    const auto m_rotation = glm::inverse(glm::mat4(camera->calculateViewMatrix()));
    const glm::quat q_rotation = quat_cast(m_rotation);
    rigid_body->SetTransform(position, q_rotation);

    const btVector3 new_bt_scale(
        original_bt_scale.x() * (new_scale.x / original_scale.x),
        original_bt_scale.y() * (new_scale.y / original_scale.y),
        original_bt_scale.z() * (new_scale.z / original_scale.z)
    );
    rigid_body->GetCollisionShape()->setLocalScaling(new_bt_scale);
}
