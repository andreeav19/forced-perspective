#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Material.h"
#include "Shader.h"
#include "Application.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coord;
};

class Mesh {
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::shared_ptr<Material> material;

    void SetupMesh();

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh() = default;

    void Render(const glm::mat4 &model) const;
};
