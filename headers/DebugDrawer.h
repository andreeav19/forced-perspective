#pragma once

#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Constants.h"

#include "Shader.h"
#include "LinearMath/btIDebugDraw.h"

class DebugDrawer : public btIDebugDraw {
    int debug_mode = DBG_DrawWireframe;

    unsigned int debug_shader;
    unsigned int ul_view, ul_projection;
    unsigned int VAO, VBO;

    std::pmr::vector<float> vertices;

    void SetupDebugShader();
    void SetupBuffers();

public:
    DebugDrawer() = default;
    ~DebugDrawer() override = default;

    void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override;
    void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB,
        btScalar distance, int lifeTime, const btVector3 &color) override {}
    void draw3dText(const btVector3 &location, const char *textString) override {};
    void setDebugMode(int debugMode) override { debug_mode = debugMode; }
    void reportErrorWarning(const char *warningString) override {}
    int getDebugMode() const override { return debug_mode; }

    void Render(const glm::mat4 &view, const glm::mat4 &projection);
};
