#include "../headers/Material.h"

#include "../headers/TextureManager.h"

Material::Material(unsigned int diffuse_map, unsigned int specular_map, float shininess)
    : diffuse_map(diffuse_map), specular_map(specular_map), shininess(shininess) {}

Material::Material()
{
    diffuse_map = 0;
    specular_map = 1;
    shininess = 32;
}

void Material::UseTextures() const
{
    TextureManager::useTexture(diffuse_map, 0);
    TextureManager::useTexture(specular_map, 1);
}
