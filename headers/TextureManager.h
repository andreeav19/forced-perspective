#pragma once

#include <filesystem>
#include <iostream>
#include <string>

#include <glad/glad.h>

class TextureManager {
    // temp
    unsigned int texture = 0;

public:
    static void useTexture(unsigned int texture_id, unsigned int unit);

    int loadTexture(const std::string &filename);
};
