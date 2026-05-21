#include "../headers/DebugDrawer.h"

void DebugDrawer::SetupDebugShader()
{
    Shader::initShaderProgram(debug_shader, "debug_vertex.glsl", "debug_fragment.glsl");

    // uniforms
    ul_view = glGetUniformLocation(debug_shader, "view");
    if (ul_view == -1) std::cout << "Error getting uniform location for view." << std::endl;

    ul_projection = glGetUniformLocation(debug_shader, "projection");
    if (ul_projection == -1) std::cout << "Error getting uniform location for projection." << std::endl;
}

void DebugDrawer::SetupBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    6 * sizeof(float), static_cast<void *>(nullptr));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));

    glBindVertexArray(0);
}

DebugDrawer::DebugDrawer()
{
    SetupDebugShader();
    SetupBuffers();
}

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
    vertices.insert(vertices.end(), {
        from.x(), from.y(), from.z(), color.x(), color.y(), color.z(),
        to.x(),   to.y(),   to.z(),   color.x(), color.y(), color.z()
    });
}

void DebugDrawer::Render(const glm::mat4 &view, const glm::mat4 &projection)
{
    if (vertices.empty()) return;

    glUseProgram(debug_shader);

    glUniformMatrix4fv(ul_view, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(ul_projection, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

    glDrawArrays(GL_LINES, 0, vertices.size() / 6);

    glBindVertexArray(0);
    glUseProgram(0);

    vertices.clear();
}
