#pragma once

#include "Mesh.h"
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWindow>
#include "Shader.h"

class TriangleWindow : public QOpenGLWindow, protected QOpenGLExtraFunctions
{
public:
    TriangleWindow();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    GLint m_projectionUniform, m_viewUniform, m_modelUniform = 0;
    QMatrix4x4 m_projection, m_view, m_model;
    Mesh* m_mesh = nullptr;
    QOpenGLVertexArrayObject* m_vao = nullptr;
    QOpenGLBuffer* m_vbo, *m_ibo = nullptr;
    QOpenGLShaderProgram* m_program = nullptr;
    Shader* shader = nullptr;
    int m_frame = 0;
    GLfloat angle = 0.0f;

    bool m_uniformsDirty = true; // Specify if uniform values have changed
};