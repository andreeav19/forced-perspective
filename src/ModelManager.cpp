#include "../headers/ModelManager.h"

void ModelManager::init()
{
    models.emplace_back("backpack.obj");
    models.emplace_back("room.obj");
    models.emplace_back("props.obj");
}

void ModelManager::render()
{
    auto position = glm::vec3(-2.0f, -0.5f, 1.0f);
    auto model = glm::mat4(1.0f);
    model = translate(model, position);
    models[1].Render(model);

    position = glm::vec3(-3.0f, -0.8f, 2.0f);
    model = glm::mat4(1.0f);
    model = translate(model, position);
    models[2].Render(model);
}

void ModelManager::clear() const
{
    for (const auto& model: models) {
        model.Clear();
    }
}
