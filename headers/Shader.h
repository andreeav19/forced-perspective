#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
    unsigned int shader_program;
    int ul_model, ul_view, ul_projection;
    int ul_ambience, ul_light_pos, ul_light_color;
    int ul_view_position;

    static std::string loadShaderSource(const std::string& filename);
    static bool initShader(unsigned int& shader, GLenum shaderType, const std::string &filename);
    void initUniform(int& uniformLocation, const std::string &uniformName) const;
    void initUniforms();
    void useUniforms();

public:
    Shader() = default;

    bool init();
    void use() const;

    void SetUniformModel(glm::mat4 model) const;
    void SetUniformView(glm::mat4 view) const;
    void SetUniformProjection(glm::mat4 projection) const;
    void SetUniformAmbienceStrength(float ambience) const;
    void SetUniformLightPosition(glm::vec3 light_position) const;
    void SetUniformLightColor(glm::vec3 light_color) const;
    void SetUniformViewPosition(glm::vec3 view_position) const;
};
