#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    MainWindow mainWindow;
    mainWindow.setWindowFlags(mainWindow.windowFlags() | Qt::WindowStaysOnTopHint);
    mainWindow.show();
    
    return app.exec();
}