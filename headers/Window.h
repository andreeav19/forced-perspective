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

    GLFWwindow *GetWindow() const { return window.get(); }

    void init();
    bool createWindow();
    bool load();
    bool shouldClose() const;
    void clear() const;
    void terminate() const;

    void pollEvents() const;
    void swapBuffers() const;
};