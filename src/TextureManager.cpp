#include "../headers/TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

void TextureManager::loadTexture(const std::string &filename)
{
    const std::filesystem::path file_path = std::filesystem::path(PROJECT_ROOT)/ "textures" / filename;
    int width = 0, height = 0, channels = 0;
    unsigned char* pixels = stbi_load(file_path.string().c_str(), &width, &height, &channels, 0);

    if (!pixels) {
        std::cout << "Error loading texture " << filename.c_str() << ": " << stbi_failure_reason() << std::endl;
        return;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
}

void TextureManager::useTexture() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}
