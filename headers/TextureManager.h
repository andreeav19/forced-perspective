#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

#include <glad/glad.h>

class TextureManager {
    std::unordered_map<std::string, unsigned int> textures;
    std::string default_texture = "white.png";

public:
    ~TextureManager();

    void init();
    void useTexture(int texture_id, unsigned int unit);

    int loadTexture(const std::string &filename);
};
