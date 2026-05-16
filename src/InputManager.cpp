#include "../headers/InputManager.h"

InputManager::InputManager(): window(nullptr), mouse_last_x(400), mouse_last_y(300),
                              mouse_x_offset(0), mouse_y_offset(0) {}

void InputManager::calculateMousePosition(const double x_pos, const double y_pos)
{
    if (first_move) {
        mouse_last_x = x_pos;
        mouse_last_y = y_pos;
        first_move = false;
    }

    mouse_x_offset = x_pos - mouse_last_x;
    mouse_y_offset = mouse_last_y - y_pos;
    mouse_last_x = x_pos;
    mouse_last_y = y_pos;

    mouse_x_offset *= sensitivity;
    mouse_y_offset *= sensitivity;
}

void InputManager::mouse_callback(GLFWwindow *window, double x_pos, double y_pos)
{
    auto self_reference = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

    if (self_reference) self_reference->calculateMousePosition(x_pos, y_pos);
}

void InputManager::SetWindow(GLFWwindow *new_window)
{
    window = new_window;
}

void InputManager::SetupMouseInput()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, mouse_callback);
}

void InputManager::ResetMouseOffsets()
{
    mouse_x_offset = 0;
    mouse_y_offset = 0;
}

bool InputManager::isActionPressed(const Action action) const
{
    if (glfwGetKey(window, key_bindings.at(action)) == GLFW_PRESS)
        return true;
    return false;
}

void InputManager::processInput() const
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
