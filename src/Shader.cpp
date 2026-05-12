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
    return true;
}

void Shader::use() const
{
    glUseProgram(shader_program);
}
