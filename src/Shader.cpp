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

bool Shader::initShaderProgram(unsigned int &shader, const std::string &vertex, const std::string &fragment)
{
    shader = glCreateProgram();
    unsigned int vertex_shader, fragment_shader;
    int success = initShader(vertex_shader, GL_VERTEX_SHADER, vertex);
    if (!success) return false;

    success = initShader(fragment_shader, GL_FRAGMENT_SHADER, fragment);
    if (!success) return false;

    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    // check errors
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error linking shader program: " << infoLog << std::endl;
        return false;
    }

    // delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
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

    for (int i = 0; i < LIGHTS_NUMBER; i++) {
        std::string light_string = "lights[" + std::to_string(i) + "].";
        initUniform(ul_light_position[i], light_string + "position");
        initUniform(ul_light_ambience[i], light_string + "ambience");
        initUniform(ul_light_diffuse[i], light_string + "diffuse");
        initUniform(ul_light_specular[i], light_string + "specular");
        initUniform(ul_light_constant[i], light_string + "constant");
        initUniform(ul_light_linear[i], light_string + "linear");
        initUniform(ul_light_quadratic[i], light_string + "quadratic");
    }

    // material
    initUniform(ul_mat_diffuse, "material.diffuse");
    initUniform(ul_mat_specular, "material.specular");
    initUniform(ul_mat_shininess, "material.shininess");
}

bool Shader::init()
{
    initShaderProgram(shader_program, "vertex.glsl", "fragment.glsl");
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

void Shader::SetUniformLight(int index, glm::vec3 light_position, glm::vec3 ambience, glm::vec3 diffuse, glm::vec3 specular,
    float constant, float linear, float quadratic) const
{
    glUniform3fv(ul_light_position[index], 1, value_ptr(light_position));
    glUniform3fv(ul_light_ambience[index], 1, value_ptr(ambience));
    glUniform3fv(ul_light_diffuse[index], 1, value_ptr(diffuse));
    glUniform3fv(ul_light_specular[index], 1, value_ptr(specular));
    glUniform1f(ul_light_constant[index], constant);
    glUniform1f(ul_light_linear[index], linear);
    glUniform1f(ul_light_quadratic[index], quadratic);
}

void Shader::SetUniformMaterial(float shininess) const
{
    glUniform1i(ul_mat_diffuse, 0);
    glUniform1i(ul_mat_specular, 1);
    glUniform1f(ul_mat_shininess, shininess);
}
