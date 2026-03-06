#include "TriangleWindow.h"

#include <QScreen>
#include "Utils.h"

static const char* vertexShaderSource = "#version 330\n"
"in highp vec4 posAttr;\n"
"in lowp vec4 colAttr;\n"
"out lowp vec4 col;\n"
"uniform highp mat4 projection;\n"
"uniform highp mat4 view;\n"
"uniform highp mat4 model;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = projection * view *model * posAttr;\n"
"}\n";

static const char* fragmentShaderSource = "#version 330\n"
"in lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";

void TriangleWindow::initialize()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2 // bottom
    };

    m_ibo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    m_ibo->create();
    m_ibo->bind();
    m_ibo->allocate(indices, sizeof(indices));

    // Tétraèdre
    GLfloat vertices[] = {
        //    x,     y,	    z,	  r,    g,    b
            -1.0f, -1.0f, -0.6f, 0.0f, 1.0f, 0.0f, // left
            +0.0f, -1.0f, +1.0f, 0.5f, 0.0f, 1.0f, // behind
            +1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, // right
            +0.0f, +1.0f, +0.0f, 1.0f, 1.0f, 1.0f, // up
    };

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));

    // Enable vertex array for the shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Fill vertex array with data: xyz Pos + rgb color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    // Create shader program from shader files
    shader = new Shader(this);
    QString vertexShaderPath;
    vertexShaderPath.append(PROJECT_ROOT).append("/Shaders/shader.vert");
    QString fragmentShaderPath;
    fragmentShaderPath.append(PROJECT_ROOT).append("/Shaders/shader.frag");
    shader->CreateFromFiles(qPrintable(vertexShaderPath), qPrintable(fragmentShaderPath));
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    shader->bind();

    // Create the matrix to apply to the triangle
    // The order is projection * view * model
    QMatrix4x4 projection;
    // Create projection matrix
    projection.perspective(60.0f, width() / height(), 0.1f, 100.0f);
    // Create the view matrix
    // keeping identity matrix so the camera is at 0, 0, 0
    QMatrix4x4 view;
    // Create the model matrix
    QMatrix4x4 model;
    model.translate(0, 0, -3);
    model.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    // pass the matrices values to the shader
    shader->setUniformValue(shader->GetUniformProjection(), projection);
    shader->setUniformValue(shader->GetUniformView(), view);
    shader->setUniformValue(shader->GetUniformModel(), model);

    // render the triangle
    // Enable the vertex arrays we created
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Draw from the data in the arrays
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    // disable the vertex arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Remove the shader from context
    shader->release();

    ++m_frame;
}