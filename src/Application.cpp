#include "../headers/Application.h"

std::unique_ptr<Application> Application::Instance = nullptr;

Application* Application::GetInstance()
{
    if (!Instance) Instance.reset(new Application());

    return Instance.get();
}

Application::Application(): vao(0), vbo(0)
{
    window = std::make_unique<Window>();
    input_manager = std::make_unique<InputManager>();
    shader = std::make_unique<Shader>();
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

    return true;
}

void Application::render() const
{
    // temp
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Application::setupShape()
{
    constexpr float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
   };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr)); // location = 0
    glEnableVertexAttribArray(0);
}

void Application::run()
{
    if (!init()) return;
    setupShape();

    while (!window->shouldClose()) {
        window->pollEvents();
        input_manager->processInput(window->GetWindow());
        window->clear();

        shader->use();
        render();

        window->swapBuffers();
    }

    window->terminate();
}
