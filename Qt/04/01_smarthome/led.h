#ifndef LED_H
#define LED_H

#include <QObject>
#include <QFile>
#include <QDebug>

class Led : public QObject
{
    Q_OBJECT
public:
    explicit Led(QObject *parent = nullptr);

    // 设置lED的状态
    void setLedState(bool flag);

signals:

private:
    // 文件
    QFile m_file;

};

#endif // LED_H
