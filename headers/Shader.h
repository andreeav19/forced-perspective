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
    int ul_view_position, ul_light_position;
    int ul_light_ambience, ul_light_diffuse, ul_light_specular;
    int ul_mat_diffuse, ul_mat_specular, ul_mat_shininess;

    static std::string loadShaderSource(const std::string& filename);
    static bool initShader(unsigned int& shader, GLenum shaderType, const std::string &filename);
    void initUniform(int& uniformLocation, const std::string &uniformName) const;
    void initUniforms();

public:
    Shader() = default;

    bool init();
    void use() const;

    void SetUniformModel(glm::mat4 model) const;
    void SetUniformView(glm::mat4 view) const;
    void SetUniformProjection(glm::mat4 projection) const;
    void SetUniformViewPosition(glm::vec3 view_position) const;
    void SetUniformLight(glm::vec3 light_position, glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular) const;
    void SetUniformMaterial(float shininess) const;
};
