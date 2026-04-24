#include "TriangleWindow.h"

#include <QScreen>
#include <QTimer>
#include "Utils.h"

TriangleWindow::TriangleWindow()
{
    // create the rendering loop
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        angle += 1.0f;
        update();
    });
    timer->start(16); // ~60 FPS
}

void TriangleWindow::initializeGL()
{
    // Init OpenGL functions to avoid errors
    // Remember that at first the openGL functions pointer points to nothing since implementation depend of GPU drivers.
    initializeOpenGLFunctions();

    unsigned int indices[] = {
        0, 1, 3, // Front
        0, 2, 1, // Left
        0, 3, 2, // Right
        2, 1, 3  // bottom
    };

    // Tétraèdre
    GLfloat vertices[] = {
        //    x,     y,	    z,	  r,    g,    b
            +0.0f, +1.0f, +0.0f, 1.0f, 1.0f, 1.0f, // up
            -1.0f, -1.0f, -0.6f, 0.0f, 1.0f, 0.0f, // left
            +0.0f, -1.0f, +1.0f, 0.5f, 0.0f, 1.0f, // behind
            +1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f // right
    };

    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();

    m_ibo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    m_ibo->create();
    m_ibo->bind();
    m_ibo->allocate(indices, sizeof(indices));

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));

    // Enable and fill the array holding vertices data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    // Enable and fill the array holding the color data
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    m_vbo->release();
    m_vao->release();

    //m_mesh = new Mesh();
    //m_mesh->CreateMesh(vertices, indices, 24, 12);

    // Create shader program from shader files
    shader = new Shader(this);
    QString vertexShaderPath;
    vertexShaderPath.append(PROJECT_ROOT).append("/Shaders/shader.vert");
    QString fragmentShaderPath;
    fragmentShaderPath.append(PROJECT_ROOT).append("/Shaders/shader.frag");
    shader->CreateFromFiles(qPrintable(vertexShaderPath), qPrintable(fragmentShaderPath));

    // Use something else than black to be sure that we're rendering something
    glClearColor(0.2f, 0.3f, 0.3f, 1);
}

// Is called every time the widget is resized and the first time it's shown
void TriangleWindow::resizeGL(int w, int h)
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void TriangleWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    shader->bind();

    // Initialize the matrices to apply to the triangle
    // The order is projection * view * model
    // The projection matrix is already set up in the resize
    // keeping identity matrix for the view matrix so the camera is at 0, 0, 0
    // Initialize the model matrix
    QMatrix4x4 model;
    model.translate(0, 0, -3);
    //m_model.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    model.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    // pass the matrices values to the shader
    shader->setUniformValue(shader->GetUniformProjection(), m_projection);
    shader->setUniformValue(shader->GetUniformView(), m_view);
    shader->setUniformValue(shader->GetUniformModel(), model);

    // render the triangle
    // Enable the vertex arrays we created
    // Draw from the data in the arrays
    m_vao->bind();
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
    // disable the vertex arrays
    m_vao->release();
    //m_mesh->RenderMesh();


    // Remove the shader from context
    shader->release();

    ++m_frame;
}