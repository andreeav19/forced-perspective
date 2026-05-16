#include "../headers/InputManager.h"

void InputManager::SetWindow(GLFWwindow *new_window)
{
    window = new_window;
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
