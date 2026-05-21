#include "../headers/PostProcess.h"

bool PostProcess::setupShaders()
{
    const bool success = Shader::initShaderProgram(dof_shader, "simple_vertex.glsl", "dof_fragment.glsl");

    ul_screen_texture = glGetUniformLocation(dof_shader, "screenTexture");
    if (ul_screen_texture == -1) {
        std::cout << "Error getting uniform location for screenTexture." << std::endl;
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
    glGenFramebuffers(1, &FBO);
    activate();

    screen_texture = texture_manager->loadFramebufferColorTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screen_texture, 0);

    depth_texture = texture_manager->loadFramebufferDepthTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Error initialising framebuffer: incomplete." << std::endl;
        return false;
    }

    deactivate();
    setupQuad();

    return setupShaders();
}

void PostProcess::activate() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcess::deactivate()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcess::renderQuad(TextureManager *texture_manager) const
{
    glUseProgram(dof_shader);
    glUniform1i(ul_screen_texture, 0);

    glBindVertexArray(VAO);
    glDisable(GL_DEPTH_TEST);

    texture_manager->useTexture(screen_texture, 0);
    // texture_manager->useTexture(depth_texture, 1);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
