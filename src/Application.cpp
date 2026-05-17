#include "../headers/Application.h"

#include "../headers/ModelManager.h"

std::unique_ptr<Application> Application::Instance = nullptr;

Application* Application::GetInstance()
{
    if (!Instance) Instance.reset(new Application());

    return Instance.get();
}

float Application::GetDeltaTime() const
{
    return delta_time;
}

Application::Application(): delta_time(0), last_frame(0)
{
    window = std::make_unique<Window>();
    input_manager = std::make_unique<InputManager>();
    texture_manager = std::make_unique<TextureManager>();
    shader = std::make_unique<Shader>();
    camera = std::make_unique<Camera>();
    action_controller = std::make_unique<ActionController>();
    light_manager = std::make_unique<LightManager>();
    model_manager = std::make_unique<ModelManager>();
}

bool Application::init() const
{
    window->init();
    const std::string error = "Failed to initialise the application";
    if (!window->createWindow()) {
        std::cout << error << std::endl;
        return false;
    }

    if (!window->load()) {
        std::cout << error << std::endl;
        return false;
    }

    if (!shader->init()) {
        std::cout << error << std::endl;
        return false;
    }

    input_manager->SetWindow(window->GetWindow());
    input_manager->SetupMouseInput();

    texture_manager->init();

    model_manager->init();

    return true;
}

void Application::render() const
{
    model_manager->render();
}

void Application::clear() const
{
    model_manager->clear();
}

void Application::updateUniforms() const
{
    const glm::mat4 view = camera->calculateViewMatrix();
    shader->SetUniformView(view);
    shader->SetUniformViewPosition(camera->GetPosition());

    light_manager->SetUniforms();
}

void Application::calculateDeltaTime()
{
    const float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
}

void Application::update() const
{
    action_controller->ControlCamera(input_manager.get(), camera.get());
}

void Application::run()
{
    if (!init()) return;

    const glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    camera->calculateCameraVectors();

    while (!window->shouldClose()) {
        calculateDeltaTime();

        window->pollEvents();
        input_manager->processInput();
        update();

        window->clear();
        shader->use();

        shader->SetUniformProjection(projection);
        updateUniforms();

        render();

        window->swapBuffers();
    }

    clear();
    window->terminate();
}
