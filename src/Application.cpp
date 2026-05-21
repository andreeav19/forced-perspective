#include "../headers/Application.h"

#include "../headers/ObjectsManager.h"
#include "../headers/ActionController.h"
#include "../headers/PhysicsSimulation.h"
#include "../headers/PostProcess.h"

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
    objects_manager = std::make_unique<ObjectsManager>();
    physics_simulation = std::make_unique<PhysicsSimulation>();
    post_process = std::make_unique<PostProcess>();
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

    objects_manager->init(physics_simulation.get());

    post_process->init(texture_manager.get());

    return true;
}

void Application::render(const glm::mat4 &view, const glm::mat4 &projection) const
{
    objects_manager->render();
    physics_simulation->Render(view, projection);
}

void Application::clear() const
{
    objects_manager->clear();
}

void Application::updateUniforms(const glm::mat4 &view, const glm::mat4 &projection) const
{
    shader->SetUniformView(view);
    shader->SetUniformViewPosition(camera->GetPosition());
    shader->SetUniformProjection(projection);
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
    action_controller->ControlDebugRender(input_manager.get(), physics_simulation.get());

    physics_simulation->Update();
    objects_manager->resetObjectsHovered();

    bool has_hit = false;
    glm::vec3 far_position = glm::vec3(0.0f);

    if (objects_manager->GetHeldGameObject() == nullptr)
        physics_simulation->UseRayCastInteractive(camera.get());
    else {
        has_hit = physics_simulation->UseRayCastPerspective(camera.get(), far_position);
    }

    action_controller->ControlPickUp(
        input_manager.get(),
        camera.get(),
        objects_manager->GetHoveredGameObject(),
        objects_manager->GetHeldGameObject()
    );

    if (!has_hit)
        objects_manager->update(camera.get());
    else
        objects_manager->update(camera.get(), far_position);
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

        const glm::mat4 view = camera->calculateViewMatrix();

        // default scene
        window->clear();
        post_process->activateScreenFramebuffer();
        shader->use();
        updateUniforms(view, projection);
        render(view, projection);

        // blurred scene
        post_process->activateBlurFramebuffer();
        post_process->useBlur(texture_manager.get());
        post_process->renderQuad();

        // dof scene
        post_process->activateDefaultFramebuffer();
        post_process->useDof(texture_manager.get(), objects_manager.get());
        post_process->renderQuad();


        window->swapBuffers();
    }

    clear();
    window->terminate();
}
