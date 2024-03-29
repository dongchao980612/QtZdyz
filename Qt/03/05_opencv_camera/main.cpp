#include "mainwindow.h"

#include <QApplication>
#include "camera.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Camera c;


    w.show();
    return a.exec();
}
