#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

class Window {
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window{nullptr, glfwDestroyWindow};
    unsigned int width;
    unsigned int height;

    static void framebuffer_size_callback(GLFWwindow *window, int w, int h);

public:
    Window();

    [[nodiscard]] GLFWwindow *GetWindow() const { return window.get(); }

    [[nodiscard]] bool ShouldClose() const;
    bool CreateWindow();
    bool Load();

    void Init();
    void Clear() const;
    void Terminate() const;

    void PollEvents() const;
    void SwapBuffers() const;
};