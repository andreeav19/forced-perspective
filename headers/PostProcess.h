#pragma once

#include <glad/glad.h>

#include "TextureManager.h"
#include "Shader.h"

class PostProcess {
    unsigned int dof_shader, blur_shader;
    unsigned int FBO_B, FBO_S;
    unsigned int VAO, VBO;
    int screen_texture, depth_texture, blur_texture;
    unsigned int ul_dof_screen_texture, ul_dof_depth_texture, ul_dof_blur_texture,
                 ul_blur_screen_texture;

    bool setupShaders();
    void setupQuad();

public:
    PostProcess() = default;
    ~PostProcess() = default;

    bool init(TextureManager *texture_manager);

    void activateBlurFramebuffer() const;
    void activateScreenFramebuffer() const;
    void activateDefaultFramebuffer();

    void renderQuad() const;
    void useBlur(TextureManager* texture_manager) const;
    void useDof(TextureManager* texture_manager) const;
};