#pragma once

#include <glad/glad.h>

#include "ObjectsManager.h"
#include "TextureManager.h"
#include "Shader.h"

class PostProcess {
    unsigned int dof_shader, blur_shader;
    unsigned int FBO_B, FBO_S;
    unsigned int VAO, VBO;
    int screen_texture, depth_texture, blur_texture;
    unsigned int ul_dof_screen_texture, ul_dof_depth_texture, ul_dof_blur_texture,
                 ul_blur_screen_texture, ul_dof_is_held;

    bool SetupShaders();
    void SetupQuad();

public:
    PostProcess() = default;
    ~PostProcess() = default;

    bool Init(TextureManager *texture_manager);

    void ActivateBlurFramebuffer() const;
    void ActivateScreenFramebuffer() const;
    void ActivateDefaultFramebuffer();

    void RenderQuad() const;
    void UseBlur(TextureManager* texture_manager) const;
    void UseDof(TextureManager* texture_manager, ObjectsManager* objects_manager) const;
};