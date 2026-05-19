#pragma once

#include <GLFW/glfw3.h>

#include "InputAction.h"

class InputManager {
    GLFWwindow* window;

    const float sensitivity = 0.3f;
    bool first_move = true;
    float mouse_last_x, mouse_last_y;
    float mouse_x_offset, mouse_y_offset;

    void calculateMousePosition(double x_pos, double y_pos);
    static void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);

public:
    InputManager();
    ~InputManager() = default;

    [[nodiscard]] float GetMouseXOffset() const { return mouse_x_offset; }
    [[nodiscard]] float GetMouseYOffset() const { return mouse_y_offset; }

    void SetWindow(GLFWwindow* new_window);

    void SetupMouseInput();
    void ResetMouseOffsets();
    void processInput() const;
    bool isActionPressed(Action action) const;
    bool isLeftClickPressed() const;
};
