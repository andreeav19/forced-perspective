#include "../headers/TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

int TextureManager::LoadTexture(const std::string &filename)
{
    if (textures.contains(filename)) return textures[filename];

    const std::filesystem::path file_path = std::filesystem::path(PROJECT_ROOT)/ "textures" / filename;
    int width = 0, height = 0, channels = 0;
    unsigned char* pixels = stbi_load(file_path.string().c_str(), &width, &height, &channels, 4);

    if (!pixels) {
        std::cout << "Error loading texture " << file_path.string() << ": " << stbi_failure_reason() << std::endl;
        return -1;
    }

    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
    textures[filename] = texture_id;
    return texture_id;
}

int TextureManager::LoadFramebufferColorTexture()
{
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const std::string name = "framebuffer" + std::to_string(texture_id);
    textures[name] = texture_id;
    return texture_id;
}

int TextureManager::LoadFramebufferDepthTexture()
{
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const std::string name = "framebuffer" + std::to_string(texture_id);
    textures[name] = texture_id;
    return texture_id;
}

TextureManager::~TextureManager()
{
    for (const auto& [name, texture_id] : textures)
        glDeleteTextures(1, &texture_id);
}

void TextureManager::Init()
{
    LoadTexture(default_texture);
}

void TextureManager::UseTexture(const int texture_id, const unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);

    if (texture_id > -1)
        glBindTexture(GL_TEXTURE_2D, texture_id);
    else
        glBindTexture(GL_TEXTURE_2D, textures[default_texture]);
}
