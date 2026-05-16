#pragma once
#include <memory>

#include "Window.h"
#include "InputManager.h"
#include "Shader.h"
#include "TextureManager.h"
#include "Camera.h"
#include "ActionController.h"
#include "LightManager.h"

// temp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Application {
    static std::unique_ptr<Application> Instance;

    std::unique_ptr<Window> window;
    std::unique_ptr<ActionController> action_controller;
    std::unique_ptr<InputManager> input_manager;
    std::unique_ptr<TextureManager> texture_manager;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<LightManager> light_manager;

    unsigned int vao, vbo, ebo; // temp
    float delta_time;
    float last_frame;

    Application();
    ~Application() = default;

    friend std::default_delete<Application>;

    [[nodiscard]] bool init() const;

    void render() const;
    void setupShape(); // temp
    void updateUniforms() const;

    void calculateDeltaTime();
    void update() const;
public:
    static Application* GetInstance();

    float GetDeltaTime() const;

    void run();
};
