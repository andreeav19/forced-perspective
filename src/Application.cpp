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
    light_manager = std::make_unique<LightManager>();
    objects_manager = std::make_unique<ObjectsManager>();
    physics_simulation = std::make_unique<PhysicsSimulation>();
    post_process = std::make_unique<PostProcess>();
}

bool Application::Init() const
{
    window->Init();
    const std::string error = "Failed to initialise the application";
    if (!window->CreateWindow()) {
        std::cout << error << std::endl;
        return false;
    }

    if (!window->Load()) {
        std::cout << error << std::endl;
        return false;
    }

    if (!shader->Init()) {
        std::cout << error << std::endl;
        return false;
    }

    input_manager->SetWindow(window->GetWindow());
    input_manager->SetupMouseInput();

    texture_manager->Init();

    objects_manager->Init(physics_simulation.get());

    post_process->Init(texture_manager.get());

    return true;
}

void Application::Render(const glm::mat4 &view, const glm::mat4 &projection) const
{
    objects_manager->Render();
    physics_simulation->Render(view, projection);
}

void Application::Clear() const
{
    objects_manager->Clear();
}

void Application::UpdateUniforms(const glm::mat4 &view, const glm::mat4 &projection) const
{
    shader->SetUniformView(view);
    shader->SetUniformViewPosition(camera->GetPosition());
    shader->SetUniformProjection(projection);
    light_manager->SetUniforms();
}

void Application::CalculateDeltaTime()
{
    const float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
}

void Application::Update() const
{
    ActionController::ControlCamera(input_manager.get(), camera.get());
    ActionController::ControlDebugRender(input_manager.get(), physics_simulation.get());

    physics_simulation->Update();
    objects_manager->ResetObjectsHovered();

    bool has_hit = false;
    auto far_position = glm::vec3(0.0f);

    if (objects_manager->GetHeldGameObject() == nullptr)
        physics_simulation->UseRayCastInteractive(camera.get());
    else {
        has_hit = physics_simulation->UseRayCastPerspective(camera.get(), far_position);
    }

    ActionController::ControlPickUp(
        input_manager.get(),
        camera.get(),
        objects_manager->GetHoveredGameObject(),
        objects_manager->GetHeldGameObject()
    );

    if (!has_hit)
        objects_manager->Update(camera.get());
    else
        objects_manager->Update(camera.get(), far_position);
}

void Application::run()
{
    if (!Init()) return;

    const glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    camera->CalculateCameraVectors();

    while (!window->ShouldClose()) {
        CalculateDeltaTime();

        window->PollEvents();
        input_manager->ExitApplication();
        Update();

        const glm::mat4 view = camera->CalculateViewMatrix();

        // default scene
        window->Clear();
        post_process->ActivateScreenFramebuffer();
        shader->Use();
        UpdateUniforms(view, projection);
        Render(view, projection);

        // blurred scene
        post_process->ActivateBlurFramebuffer();
        post_process->UseBlur(texture_manager.get());
        post_process->RenderQuad();

        // dof scene
        post_process->ActivateDefaultFramebuffer();
        post_process->UseDof(texture_manager.get(), objects_manager.get());
        post_process->RenderQuad();

        window->SwapBuffers();
    }

    Clear();
    window->Terminate();
}
