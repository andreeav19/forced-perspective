#pragma once
#include <memory>

#include "Window.h"
#include "InputManager.h"

class Application {
    static std::unique_ptr<Application> Instance;

    std::unique_ptr<Window> window;
    std::unique_ptr<InputManager> input_manager;

    Application();
    ~Application() = default;

    friend std::default_delete<Application>;

    bool init() const;
    void render() const;
public:
    static Application* GetInstance();

    void run() const;
};
