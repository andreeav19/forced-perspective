#pragma once

class Material {
    unsigned int diffuse_map;
    unsigned int specular_map;
    float shininess;

public:
    Material();
    Material(unsigned int diffuse_map, unsigned int specular_map, float shininess);

    [[nodiscard]] float GetShininess() const { return shininess; }

    void SetDiffuseMap(const unsigned int new_diffuse) { diffuse_map = new_diffuse; }
    void SetSpecularMap(const unsigned int new_specular) { specular_map = new_specular; }

    void UseTextures() const;
};