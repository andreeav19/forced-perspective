#include "../headers/Application.h"

std::unique_ptr<Application> Application::Instance = nullptr;

Application* Application::GetInstance()
{
    if (!Instance) Instance.reset(new Application());

    return Instance.get();
}

Application::Application()
{
    window = std::make_unique<Window>();
    input_manager = std::make_unique<InputManager>();
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

    return true;
}

void Application::render() const
{
}

void Application::run() const
{
    if (!init()) return;

    while (!window->shouldClose()) {
        window->pollEvents();
        input_manager->processInput(window->GetWindow());
        window->clear();

        render();

        window->swapBuffers();
    }

    window->terminate();
}
