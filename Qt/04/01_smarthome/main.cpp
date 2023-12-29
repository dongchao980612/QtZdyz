#include "mainwindow.h"

#include <QApplication>
#include "esp82266.h"
#include "webapi.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Esp82266 e;
    Webapi web;
    w.show();
    return a.exec();
}
