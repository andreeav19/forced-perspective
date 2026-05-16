#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"

class Application;

class Camera {
    glm::vec3 position;
    glm::vec3 target;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    float yaw, pitch;
    float move_speed = 1.0f;

public:
    Camera();
    ~Camera() = default;

    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetFront() const { return front; }
    glm::vec3 GetRight() const { return right; }

    void calculateCameraVectors();
    void move(glm::vec3 direction);
    void orient(double mouse_x, double mouse_y);
    glm::mat4 calculateViewMatrix() const;
};
