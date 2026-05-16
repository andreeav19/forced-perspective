#include "../headers/Camera.h"
#include "../headers/Application.h"

Camera::Camera()
{
    constexpr auto zero = glm::vec3(0);
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    target = zero;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    right = zero;
    up = zero;
}

void Camera::calculateCameraVectors()
{
    front = normalize(target - position);
    right = normalize(cross(world_up, front));
    up = normalize(cross(front, right));
}

glm::mat4 Camera::calculateViewMatrix() const
{
    return lookAt(position, position + front, up);
}

void Camera::move(const glm::vec3 direction)
{
    position += direction * move_speed * Application::GetInstance()->GetDeltaTime();
}


