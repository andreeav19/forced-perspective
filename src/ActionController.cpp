#include "../headers/ActionController.h"

void ActionController::ControlCameraMovement(const InputManager *input_manager, Camera *camera)
{
    glm::vec3 direction(0.0f);

    if (input_manager->isActionPressed(Action::MoveLeft))
        direction += camera->GetRight();
    if (input_manager->isActionPressed(Action::MoveRight))
        direction -= camera->GetRight();
    if (input_manager->isActionPressed(Action::MoveFront))
        direction += camera->GetFront();
    if (input_manager->isActionPressed(Action::MoveBack))
        direction -= camera->GetFront();

    if (length(direction) > 0.0f)
        direction = normalize(direction);

    direction.y = 0.0f; // temp solution
    camera->move(direction);
}

void ActionController::ControlCameraOrientation(InputManager *input_manager, Camera *camera)
{
    camera->orient(input_manager->GetMouseXOffset(), input_manager->GetMouseYOffset());
    input_manager->ResetMouseOffsets();
}

void ActionController::ControlCamera(InputManager *input_manager, Camera *camera)
{
    ControlCameraMovement(input_manager, camera);
    ControlCameraOrientation(input_manager, camera);
}

void ActionController::ControlDebugRender(const InputManager *input_manager, PhysicsSimulation *physics_simulation)
{
    static bool was_pressed = false;
    const bool is_pressed = input_manager->isActionPressed(Action::SwitchDebug);
    if (is_pressed && !was_pressed)
        physics_simulation->EnableDebugDraw();
    was_pressed = is_pressed;
}

void ActionController::ControlPickUp(const InputManager *input_manager, const Camera *camera, GameObject *hovered,
    GameObject *&held)
{
    const bool is_clicked = input_manager->isLeftClickPressed();

    if (hovered && hovered->IsHovered() && is_clicked && held == nullptr) {
        held = hovered;
        held->SetPickUpActive(true, camera);
    }
    else if (!is_clicked && held != nullptr) {
        held->SetPickUpActive(false, camera);
        held = nullptr;
    }
}
