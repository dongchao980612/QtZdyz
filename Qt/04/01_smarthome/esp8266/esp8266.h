#ifndef ESP8266_H
#define ESP8266_H

#include <QObject>

class esp8266 : public QObject
{
    Q_OBJECT

public:
    esp8266(QWidget *parent = nullptr);
    ~esp8266();
};
#endif // ESP8266_H
