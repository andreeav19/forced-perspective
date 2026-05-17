#pragma once

#include "TextureManager.h"

class Material {
    int diffuse_map;
    int specular_map;
    float shininess;

public:
    Material();
    Material(int diffuse_map, int specular_map, float shininess);

    [[nodiscard]] float GetShininess() const { return shininess; }

    void SetDiffuseMap(const int new_diffuse) { diffuse_map = new_diffuse; }
    void SetSpecularMap(const int new_specular) { specular_map = new_specular; }

    void UseTextures() const;
};
