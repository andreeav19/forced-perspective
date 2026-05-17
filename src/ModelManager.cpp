#include "../headers/ModelManager.h"

void ModelManager::init()
{
    auto model = Model("backpack.obj");
    models.push_back(model);
}

void ModelManager::render()
{
    models.front().Render(glm::mat4(1.0f));
}

void ModelManager::clear() const
{
    for (const auto& model: models) {
        model.Clear();
    }
}
