#include "../headers/ObjectsManager.h"

#include "../headers/ActionController.h"

void ObjectsManager::resetObjectsHovered()
{
    for (const auto& game_object: game_objects)
        game_object->SetHovered(false);
}

GameObject* ObjectsManager::GetHoveredGameObject() const
{
    for (const auto& game_object : game_objects) {
        if (game_object->IsHovered())
            return game_object.get();
    }

    return nullptr;
}

void ObjectsManager::init(const PhysicsSimulation* physics_simulation)
{
    models.emplace_back("backpack.obj");
    models.emplace_back("room.obj");
    models.emplace_back("props.obj");

    auto position = glm::vec3(0.0f, 0.01f, 1.0f);
    auto sc = glm::vec3(0.1f);

    // backpack
    game_objects.emplace_back(std::make_unique<GameObject>(models[0], position, sc, glm::vec3(0)));
    game_objects.back()->AddRigidBody(RigidBody::CreateBackpackShape(), 5);
    game_objects.back()->EnableInteractive();

    // room
    position = glm::vec3(-2.0f, -0.5f, 1.0f);
    game_objects.emplace_back(std::make_unique<GameObject>(models[1], position, glm::vec3(1), glm::vec3(0)));
    game_objects.back()->AddRigidBody(RigidBody::CreateRoomShape());

    // furniture
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

void ObjectsManager::render()
{
    for (const auto& game_object : game_objects)
        game_object->Render();
}

void ObjectsManager::update(const Camera* camera) const
{
    if (held_game_object)
        held_game_object->UpdateHoldPosition(camera);
}

void ObjectsManager::clear() const
{
    for (const auto& model: models) {
        model.Clear();
    }
}
