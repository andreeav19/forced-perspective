#include "../headers/ActionController.h"

void ActionController::ControlCamera(const InputManager *input_manager, Camera *camera)
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
    camera->move(direction);
}
