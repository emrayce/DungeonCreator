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
    format.setSamples(16);

    // Initialize 
    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}