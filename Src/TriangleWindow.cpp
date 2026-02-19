#include "TriangleWindow.h"

#include <QScreen>


static const char* vertexShaderSource = "attribute highp vec4 posAttr;\n"
"attribute lowp vec4 colAttr;\n"
"varying lowp vec4 col;\n"
"uniform highp mat4 matrix;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = matrix * posAttr;\n"
"}\n";

static const char* fragmentShaderSource = "varying lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";

void TriangleWindow::initialize()
{
    // v
    static const GLfloat vertices_colors[] = { +0.0f, +0.707f, 1.0f, 0.0f, 0.0f,
                                               -0.5f, -0.500f, 0.0f, 1.0f, 0.0f,
                                               +0.5f, -0.500f, 0.0f, 0.0f, 1.0f };

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices_colors, sizeof(vertices_colors));
    // Enable vertex array for the shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Fill vertex array with data: xy Pos + rgb color
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
        reinterpret_cast<void*>(2 * sizeof(GLfloat)));

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    // Associate variable name to the vertex arrays we created
    m_program->bindAttributeLocation("posAttr", 0);
    m_program->bindAttributeLocation("colAttr", 1);
    m_program->link();
    m_program->bind();
    // Get location/id of uniform varaible matrix
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    // Create the matrix to apply to the triangle
    // The order is projection * view * model
    // No view matrix here meaning that the camera is the center of the world
    QMatrix4x4 matrix;
    // Create projection matrix
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Create the model matrix
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    // pass the matrix value to the shader
    m_program->setUniformValue(m_matrixUniform, matrix);

    // render the triangle
    // Enable the vertex arrays we created
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Draw from the data in the arrays
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // disable the vertex arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Use the active shader program
    m_program->release();

    ++m_frame;
}