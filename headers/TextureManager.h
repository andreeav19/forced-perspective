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

    void Init();
    void UseTexture(int texture_id, unsigned int unit);

    int LoadTexture(const std::string &filename);
    int LoadFramebufferColorTexture();
    int LoadFramebufferDepthTexture();
};
