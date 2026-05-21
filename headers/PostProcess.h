#pragma once

#include <glad/glad.h>

#include "TextureManager.h"
#include "Shader.h"

class PostProcess {
    unsigned int dof_shader, blur_shader;
    unsigned int FBO;
    unsigned int VAO, VBO;
    unsigned int screen_texture, depth_texture, blur_texture;
    unsigned int ul_screen_texture;

    bool setupShaders();
    void setupQuad();

public:
    PostProcess() = default;
    ~PostProcess() = default;

    bool init(TextureManager *texture_manager);
    void activate() const;
    static void deactivate();
    void renderQuad(TextureManager* texture_manager) const;
};
