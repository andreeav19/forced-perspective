#include "../headers/ObjectsManager.h"

void ObjectsManager::init()
{
    physics_simulation = std::make_unique<PhysicsSimulation>();

    models.emplace_back("backpack.obj");
    models.emplace_back("room.obj");
    models.emplace_back("props.obj");

    auto position = glm::vec3(0.0f, 0.01f, 1.0f);
    auto sc = glm::vec3(0.1f);

    game_objects.emplace_back(std::make_unique<GameObject>(models[0], position, sc, glm::vec3(0)));
    game_objects.back()->AddRigidBody(RigidBody::CreateBackpackShape(), 5);

    position = glm::vec3(-2.0f, -0.5f, 1.0f);
    game_objects.emplace_back(std::make_unique<GameObject>(models[1], position, glm::vec3(1), glm::vec3(0)));
    game_objects.back()->AddRigidBody(RigidBody::CreateRoomShape());

    position = glm::vec3(-3.0f, -0.8f, 2.0f);
    game_objects.emplace_back(std::make_unique<GameObject>(models[2], position, glm::vec3(1), glm::vec3(0)));
    game_objects.back()->AddRigidBody(RigidBody::CreatePropsShape());

    is_debug_enabled = false;

    for (const auto& game_object : game_objects) {
        physics_simulation->AddRigidBody(
            game_object->GetRigidBody()
        );
    }
}

void ObjectsManager::render(const glm::mat4 &view, const glm::mat4 &projection)
{
    for (const auto& game_object : game_objects) {
        game_object->Render();
    }

    physics_simulation->Render(view, projection);
}

void ObjectsManager::update() const
{
    physics_simulation->Update();
}

void ObjectsManager::switchDebugRender()
{
    is_debug_enabled = !is_debug_enabled;
    physics_simulation->EnableDebugDraw(is_debug_enabled);
}

void ObjectsManager::clear() const
{
    for (const auto& model: models) {
        model.Clear();
    }
}
