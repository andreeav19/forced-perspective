#include "../headers/Scene.h"

void Scene::init()
{
    auto model = Model("backpack.obj");
    models.push_back(model);
}

void Scene::render()
{
    models.front().Render(glm::mat4(1.0f));
}
