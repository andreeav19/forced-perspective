#include "../headers/Shader.h"

std::string Shader::loadShaderSource(const std::string& filename)
{
    const std::filesystem::path file_path = std::filesystem::path(PROJECT_ROOT)/ "shaders" / filename;
    std::ifstream file(file_path);

    if (!file) {
        std::cout << "Could not open file " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

bool Shader::initShader(unsigned int& shader, const GLenum shaderType, const std::string& filename)
{
    shader = glCreateShader(shaderType);
    const std::string source = loadShaderSource(filename);
    const GLchar* vertShader = source.c_str();
    glShaderSource(shader, 1, &vertShader, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error compiling shader " << filename << ": " << infoLog << std::endl;
        return false;
    }

    return true;
}

void Shader::initUniform(int& uniformLocation, const std::string &uniformName) const
{
    uniformLocation = glGetUniformLocation(shader_program, uniformName.c_str());
    if (uniformLocation == -1) {
        std::cout << "Error getting uniform location for: " << uniformName << std::endl;
    }
}

void Shader::initUniforms()
{
    // transforms
    initUniform(ul_model, "model");
    initUniform(ul_view, "view");
    initUniform(ul_projection, "projection");

    // light
    initUniform(ul_view_position, "viewPos");
    initUniform(ul_light_position, "light.position");
    initUniform(ul_light_ambience, "light.ambience");
    initUniform(ul_light_diffuse, "light.diffuse");
    initUniform(ul_light_specular, "light.specular");

    // material
    initUniform(ul_mat_ambience, "material.ambience");
    initUniform(ul_mat_diffuse, "material.diffuse");
    initUniform(ul_mat_specular, "material.specular");
    initUniform(ul_mat_shininess, "material.shininess");
}

bool Shader::init()
{
    // add shaders
    shader_program = glCreateProgram();
    unsigned int vertex_shader, fragment_shader;
    int success = initShader(vertex_shader, GL_VERTEX_SHADER, "vertex.glsl");
    if (!success) return false;

    success = initShader(fragment_shader, GL_FRAGMENT_SHADER, "fragment.glsl");
    if (!success) return false;

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // check errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
        std::cout << "Error linking shader program: " << infoLog << std::endl;
        return false;
    }

    // delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    initUniforms();
    return true;
}

void Shader::use() const
{
    glUseProgram(shader_program);
}

void Shader::SetUniformModel(glm::mat4 model) const
{
    glUniformMatrix4fv(ul_model, 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::SetUniformView(glm::mat4 view) const
{
    glUniformMatrix4fv(ul_view, 1, GL_FALSE, glm::value_ptr(view));
}

void Shader::SetUniformProjection(glm::mat4 projection) const
{
    glUniformMatrix4fv(ul_projection, 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::SetUniformViewPosition(glm::vec3 view_position) const
{
    glUniform3fv(ul_view_position, 1, value_ptr(view_position));
}

void Shader::SetUniformLight(glm::vec3 light_position, glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular) const
{
    glUniform3fv(ul_light_ambience, 1, value_ptr(light_position));
    glUniform3fv(ul_light_ambience, 1, value_ptr(ambience));
    glUniform3fv(ul_light_diffuse, 1, value_ptr(diffuse));
    glUniform3fv(ul_light_specular, 1, value_ptr(specular));
}

void Shader::SetUniformMaterial(glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular, float shininess) const
{
    glUniform3fv(ul_mat_ambience, 1, value_ptr(ambience));
    glUniform3fv(ul_mat_diffuse, 1, value_ptr(diffuse));
    glUniform3fv(ul_mat_specular, 1, value_ptr(specular));
    glUniform1f(ul_mat_shininess, shininess);
}
