#pragma once

#define LIGHTS_NUMBER 4
#define TIME_STEP (1.0f / 60.0f)
#define MAX_SUB_STEPS 10
#define RAY_CAST_LENGTH 10
#define RAY_GRID_LENGTH 20
#define RAY_DISTANCE (0.05f)

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline auto world_up = glm::vec3(0.0f, 1.0f, 0.0f);

