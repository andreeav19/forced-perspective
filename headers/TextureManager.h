#pragma once

#include <filesystem>
#include <iostream>
#include <string>

#include <glad/glad.h>

class TextureManager {
    // temp
    unsigned int texture = 0;

public:
    void loadTexture(const std::string &filename);
    void useTexture() const; // temp
};
