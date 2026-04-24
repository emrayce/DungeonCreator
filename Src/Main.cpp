// Main.cpp : Defines the entry point for the application.
//

#include "DungeonCreator.h"

#include <QGuiApplication>
#include <QSurfaceFormat>
#include "TriangleWindow.h"

using namespace std;

int main(int argc, char** argv)
{ 
    QGuiApplication app(argc, argv);

    // Set up multisampling
    QSurfaceFormat format;
    /*if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 3.3 core context");
        format.setVersion(3, 3);
        format.setProfile(QSurfaceFormat::CoreProfile);
    }
    else {
        qDebug("Requesting 3.0 context");
        format.setVersion(3, 0);
    }*/
    QSurfaceFormat::setDefaultFormat(format);


    // Initialize 
    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

   return app.exec();
}