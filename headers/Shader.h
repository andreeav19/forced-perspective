#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>

class Shader {
    unsigned int shader_program;

    static std::string loadShaderSource(const std::string& filename);
    static bool initShader(unsigned int& shader, GLenum shaderType, const std::string &filename);

public:
    Shader() = default;

    bool init();
    void use() const;
};
