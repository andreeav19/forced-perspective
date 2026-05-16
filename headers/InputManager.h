#pragma once

#include <GLFW/glfw3.h>

#include "InputAction.h"

class InputManager {
    GLFWwindow* window;

public:
    InputManager() = default;
    ~InputManager() = default;

    void SetWindow(GLFWwindow* new_window);

    bool isActionPressed(Action action) const;
    void processInput() const;
};
