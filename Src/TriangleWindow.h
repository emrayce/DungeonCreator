#pragma once

#include "OpenGLWindow.h"
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
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
    QOpenGLVertexArrayObject* m_vao = nullptr;
    QOpenGLBuffer* m_vbo, *m_ibo = nullptr;
    QOpenGLShaderProgram* m_program = nullptr;
    Shader* shader = nullptr;
    int m_frame = 0;
};