#pragma once

#include "Camera.h"
#include "InputManager.h"

class ActionController {
    static void ControlCameraMovement(const InputManager* input_manager, Camera* camera);
    static void ControlCameraOrientation(InputManager* input_manager, Camera* camera);
public:
    static void ControlCamera(InputManager* input_manager, Camera* camera);
};
