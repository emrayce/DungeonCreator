#pragma once
/*
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QOpenGLWindow>


class OpenGLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT
public:
    explicit OpenGLWindow(QWindow* parent = nullptr);
    //~OpenGLWindow();

    virtual void render(QPainter* painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent* event) override;

    void exposeEvent(QExposeEvent* event) override;

private:
    bool m_animating = false;

    QOpenGLContext* m_context = nullptr;        // The openGL Context to draw a frame
    QOpenGLPaintDevice* m_device = nullptr;     // The tool to draw with an openGL context
};*/