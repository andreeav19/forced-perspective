#pragma once
#include <memory>

#include "Window.h"
#include "InputManager.h"
#include "Shader.h"

class Application {
    static std::unique_ptr<Application> Instance;

    std::unique_ptr<Window> window;
    std::unique_ptr<InputManager> input_manager;
    std::unique_ptr<Shader> shader;
    unsigned int vao, vbo, ebo; // temp

    Application();
    ~Application() = default;

    friend std::default_delete<Application>;

    bool init() const;
    void render() const;
    void setupShape(); // temp
public:
    static Application* GetInstance();

    void run();
};
