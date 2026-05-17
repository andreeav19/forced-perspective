#include "../headers/Model.h"

void Model::loadModel(std::string filename)
{
    const std::filesystem::path file_path = std::filesystem::path(PROJECT_ROOT)/ "models" / filename;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file_path.string().c_str(), aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Error loading assimp scene: " << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode *node, const aiScene *scene)
{
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(ai_mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex = processVertexData(mesh, i);
        vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    const aiMaterial* ai_material = scene->mMaterials[mesh->mMaterialIndex];
    const auto diffuse_map = processTextureData(ai_material, aiTextureType_DIFFUSE);
    const auto specular_map = processTextureData(ai_material, aiTextureType_SPECULAR);
    float shininess = 32.0f;
    ai_material->Get(AI_MATKEY_SHININESS, shininess);
    std::shared_ptr material = std::make_shared<Material>(diffuse_map, specular_map, shininess);

    return Mesh(vertices, indices, std::move(material));
}

Vertex Model::processVertexData(const aiMesh *mesh, const int index)
{
    Vertex vertex;
    glm::vec3 m_vector;
    m_vector.x = mesh->mVertices[index].x;
    m_vector.y = mesh->mVertices[index].y;
    m_vector.z = mesh->mVertices[index].z;
    vertex.position = m_vector;

    if (mesh->HasNormals()) {
        m_vector.x = mesh->mNormals[index].x;
        m_vector.y = mesh->mNormals[index].y;
        m_vector.z = mesh->mNormals[index].z;
        vertex.normal = m_vector;
    }
    else
        vertex.normal = glm::vec3(0.0f);

    if (mesh->HasTextureCoords(0)) {
        glm::vec2 m_texture;
        m_texture.x = mesh->mTextureCoords[0][index].x;
        m_texture.y = mesh->mTextureCoords[0][index].y;
        vertex.texture_coord = m_texture;
    }
    else {
        std::cout << "no texture coords" << std::endl;
        vertex.texture_coord = glm::vec2(0.0f);
    }

    return vertex;
}

int Model::processTextureData(const aiMaterial *material, const aiTextureType texture_type)
{
    if (material->GetTextureCount(texture_type) > 0) {
        aiString ai_string;
        material->GetTexture(texture_type, 0, &ai_string);

        std::filesystem::path texture_path = ai_string.C_Str();
        texture_path = texture_path.filename();

        const auto& texture_manager = Application::GetInstance()->GetTextureManager();
        return texture_manager->loadTexture(texture_path.string());
    }

    return -1;
}

Model::Model(const std::string &filename)
{
    loadModel(filename);
}

void Model::Clear() const
{
    for (const auto& mesh: meshes)
        mesh.Clear();
}

void Model::Render(glm::mat4 model)
{
    for (const auto& mesh: meshes)
        mesh.Render(model);
}
