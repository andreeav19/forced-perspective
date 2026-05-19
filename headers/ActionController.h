#pragma once

#include "ObjectsManager.h"
#include "Camera.h"
#include "InputManager.h"

class ActionController {
    static void ControlCameraMovement(const InputManager* input_manager, Camera* camera);
    static void ControlCameraOrientation(InputManager* input_manager, Camera* camera);
public:
    static void ControlCamera(InputManager* input_manager, Camera* camera);
    static void ControlDebugRender(const InputManager* input_manager,  PhysicsSimulation* physics_simulation);
    static void ControlPickUp(const InputManager* input_manager, const Camera* camera,
        GameObject* hovered, GameObject*& held);
};
