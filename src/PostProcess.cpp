#include "../headers/PostProcess.h"

bool PostProcess::setupShaders()
{
    bool success = Shader::initShaderProgram(dof_shader, "simple_vertex.glsl", "dof_fragment.glsl");
    if (!success) return false;

    success = Shader::initShaderProgram(blur_shader, "simple_vertex.glsl", "blur_fragment.glsl");
    if (!success) return false;

    ul_dof_screen_texture = glGetUniformLocation(dof_shader, "screenTexture");
    if (ul_dof_screen_texture == -1) {
        std::cout << "Error getting uniform location for screenTexture in dof shader." << std::endl;
        return false;
    }
    ul_dof_depth_texture = glGetUniformLocation(dof_shader, "depthTexture");
    if (ul_dof_depth_texture == -1) {
        std::cout << "Error getting uniform location for depthTexture in dof shader." << std::endl;
        return false;
    }
    ul_dof_blur_texture = glGetUniformLocation(dof_shader, "blurTexture");
    if (ul_dof_blur_texture == -1) {
        std::cout << "Error getting uniform location for blurTexture in dof shader." << std::endl;
        return false;
    }

    ul_blur_screen_texture = glGetUniformLocation(blur_shader, "screenTexture");
    if (ul_blur_screen_texture == -1) {
        std::cout << "Error getting uniform location for screenTexture in blur shader." << std::endl;
        return false;
    }

    return success;
}

void PostProcess::setupQuad()
{
    constexpr float quadVertices[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
        4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
}

bool PostProcess::init(TextureManager *texture_manager)
{
    // screen framebuffer
    glGenFramebuffers(1, &FBO_S);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_S);

    screen_texture = texture_manager->loadFramebufferColorTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screen_texture, 0);

    depth_texture = texture_manager->loadFramebufferDepthTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Error initialising screen framebuffer: incomplete." << std::endl;
        return false;
    }

    // blur framebuffer
    glGenFramebuffers(1, &FBO_B);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_B);

    blur_texture = texture_manager->loadFramebufferColorTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blur_texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Error initialising blur framebuffer: incomplete." << std::endl;
        return false;
    }

    std::cout << blur_texture << " " << screen_texture << std::endl;

    activateDefaultFramebuffer();
    setupQuad();

    return setupShaders();
}

void PostProcess::activateBlurFramebuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_B);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcess::activateScreenFramebuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_S);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcess::activateDefaultFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcess::renderQuad() const
{
    glBindVertexArray(VAO);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostProcess::useBlur(TextureManager* texture_manager) const
{
    glUseProgram(blur_shader);
    texture_manager->useTexture(screen_texture, 0);
    glUniform1i(ul_blur_screen_texture, 0);
}

void PostProcess::useDof(TextureManager *texture_manager) const
{
    glUseProgram(dof_shader);
    texture_manager->useTexture(blur_texture, 0);
    texture_manager->useTexture(depth_texture, 1);
    texture_manager->useTexture(screen_texture, 2);

    glUniform1i(ul_dof_screen_texture, 2);
    glUniform1i(ul_dof_depth_texture, 1);
    glUniform1i(ul_dof_blur_texture, 0);
}
