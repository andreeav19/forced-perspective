#pragma once
#include <memory>

#include "Window.h"
#include "InputManager.h"
#include "Shader.h"
#include "TextureManager.h"
#include "Camera.h"
#include "ActionController.h"
#include "LightManager.h"

class ModelManager;

class Application {
    static std::unique_ptr<Application> Instance;

    std::unique_ptr<Window> window;
    std::unique_ptr<ActionController> action_controller;
    std::unique_ptr<InputManager> input_manager;
    std::unique_ptr<TextureManager> texture_manager;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<LightManager> light_manager;
    std::unique_ptr<ModelManager> model_manager;

    float delta_time;
    float last_frame;

    Application();
    ~Application() = default;

    friend std::default_delete<Application>;

    [[nodiscard]] bool init() const;

    void render() const;

    void clear() const;

    void updateUniforms() const;

    void calculateDeltaTime();
    void update() const;
public:
    static Application* GetInstance();

    [[nodiscard]] float GetDeltaTime() const;
    [[nodiscard]] TextureManager* GetTextureManager() const { return texture_manager.get(); }
    [[nodiscard]] Shader* GetShader() const { return shader.get(); }

    void run();
};
