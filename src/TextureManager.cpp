#include "../headers/TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

int TextureManager::loadTexture(const std::string &filename)
{
    if (textures.contains(filename)) return textures[filename];

    const std::filesystem::path file_path = std::filesystem::path(PROJECT_ROOT)/ "textures" / filename;
    int width = 0, height = 0, channels = 0;
    unsigned char* pixels = stbi_load(file_path.string().c_str(), &width, &height, &channels, 0);

    if (!pixels) {
        std::cout << "Error loading texture " << filename.c_str() << ": " << stbi_failure_reason() << std::endl;
        return -1;
    }

    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;
    if (channels == 3) format = GL_RGB;
    else if (channels == 4) format = GL_RGBA;
    else {
        std::cout << "Error loading texture " << filename.c_str() << ": " << "unsupported format." << std::endl;
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
    textures[filename] = texture_id;
    return texture_id;
}

TextureManager::~TextureManager()
{
    for (const auto& [name, texture_id] : textures)
        glDeleteTextures(1, &texture_id);
}

void TextureManager::init()
{
    loadTexture(default_texture);
}

void TextureManager::useTexture(const int texture_id, const unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);

    if (texture_id > -1)
        glBindTexture(GL_TEXTURE_2D, texture_id);
    else
        glBindTexture(GL_TEXTURE_2D, textures[default_texture]);
}
