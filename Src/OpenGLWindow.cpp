//#include "OpenGLWindow.h"
#include <QPainter>

OpenGLWindow::OpenGLWindow(QWindow* parent)
    : QWindow(parent)
{
    // specify that we're using the surface for OpenGL
    setSurfaceType(QWindow::OpenGLSurface);
}

// Ne fait rien. C'est prévu d'utiliser le render() de la classe fille.
void OpenGLWindow::render(QPainter* painter)
{
    Q_UNUSED(painter);
}

void OpenGLWindow::initialize()
{
}

void OpenGLWindow::render()
{
    // Initialize the device to draw if it's not already defined
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    // Reset the three buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Sets the pixel size of the paint device and the pixel ratio with data from the QWindow
    m_device->setSize(size() * devicePixelRatio());
    m_device->setDevicePixelRatio(devicePixelRatio());

    // Call render with the newly created QPainter but what does it do ?
    QPainter painter(m_device);
    render(&painter);
}

void OpenGLWindow::renderLater()
{
    // Schedule a display event the next time the system is ready (either according to vsync or every 5ms)
    requestUpdate();
}

bool OpenGLWindow::event(QEvent* event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent* event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void OpenGLWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    // Create the initial context
    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    // Make the context current
    m_context->makeCurrent(this);

    if (needsInitialize) {
        // set up the dedicated openGL functions to work with the current context
        initializeOpenGLFunctions();
        initialize();
    }
    // render the frame
    render();
    // swap the buffer to display the frame we just rendered
    m_context->swapBuffers(this);

    // If there's an animation we need to render several time
    if (m_animating)
        renderLater();
}

void OpenGLWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}