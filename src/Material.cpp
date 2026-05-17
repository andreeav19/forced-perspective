#include "../headers/Material.h"

#include "../headers/Application.h"
#include "../headers/TextureManager.h"

Material::Material(int diffuse_map, int specular_map, float shininess)
    : diffuse_map(diffuse_map), specular_map(specular_map), shininess(shininess) {}

Material::Material()
{
    diffuse_map = -1;
    specular_map = -1;
    shininess = 32;
}

void Material::UseTextures() const
{
    const auto texture_manager = Application::GetInstance()->GetTextureManager();
    texture_manager->useTexture(diffuse_map, 0);
    texture_manager->useTexture(specular_map, 1);
}
