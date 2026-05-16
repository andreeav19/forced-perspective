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

    yaw = -90.0f;
    pitch = 0.0f;
}

void Camera::calculateCameraVectors()
{
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

void Camera::orient(const double mouse_x, const double mouse_y)
{
    yaw += mouse_x;
    pitch += mouse_y;

    if(pitch > 89.0f)   pitch =  89.0f;
    if(pitch < -89.0f)  pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = normalize(direction);

    calculateCameraVectors();
}


