#pragma once

#include <GLFW/glfw3.h>
#include <map>

enum class Action {
    MoveLeft,
    MoveRight,
    MoveFront,
    MoveBack,
    SwitchDebug
};

inline const std::map<Action, int> key_bindings = {
    {Action::MoveFront, GLFW_KEY_W},
    {Action::MoveLeft, GLFW_KEY_A},
    {Action::MoveBack, GLFW_KEY_S},
    {Action::MoveRight, GLFW_KEY_D},
    {Action::SwitchDebug, GLFW_KEY_T}
};
