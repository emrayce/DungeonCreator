#pragma once

#include "OpenGLWindow.h"
#include <QOpenGLBuffer>
#include "Shader.h"

class TriangleWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;

private:
    GLint m_projectionUniform, m_viewUniform, m_modelUniform = 0;
    GLuint VAO, VBO, IBO = 0;
    QOpenGLBuffer *m_vbo, *m_ibo;
    QOpenGLShaderProgram* m_program = nullptr;
    Shader* shader = nullptr;
    int m_frame = 0;
};