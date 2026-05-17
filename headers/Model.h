#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model {
    std::vector<Mesh> meshes;

    void loadModel(const std::string &filename);
    void processNode(const aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    Vertex processVertexData(const aiMesh* mesh, int index);
    int processTextureData(const aiMaterial *material, aiTextureType texture_type);

public:
    explicit Model(const std::string &filename);
    ~Model() = default;

    void Clear() const;

    void Render(glm::mat4 model=glm::mat4(1));
};
