#include <QApplication>
#include "mainwindow.h"

#ifdef _WIN32
  #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    MainWindow mainWindow;
    mainWindow.setWindowFlags(mainWindow.windowFlags() | Qt::WindowStaysOnTopHint);
    mainWindow.show();
    
    return app.exec();
}