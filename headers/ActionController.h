#pragma once

#include "Camera.h"
#include "InputManager.h"

class ActionController {
public:
    static void ControlCamera(const InputManager* input_manager, Camera* camera);
};
