#pragma once

#include "OpenGLWindow.h"
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class TriangleWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;

private:
    GLint m_matrixUniform = 0;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram* m_program = nullptr;
    int m_frame = 0;
};