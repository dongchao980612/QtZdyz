#include "esp8266.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    esp8266 w;
    w.show();
    return a.exec();
}
