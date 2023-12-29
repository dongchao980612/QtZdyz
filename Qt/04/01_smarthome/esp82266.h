#ifndef ESP82266_H
#define ESP82266_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <unistd.h>

class Esp82266 : public QObject
{
    Q_OBJECT
public:
    explicit Esp82266(QObject *parent = nullptr);
    ~Esp82266();

    /* 定时器，发送心跳包 */
    QTimer *m_timer;

    /* 接收到的数据 */
    QString m_readData = nullptr;

    /* 串口对象 */
    QSerialPort *m_serialPort;

    /* 延时函数 */
    void sleep(int);

    /* 发送命令到esp8266模块 */
    void sendCmdToEsp8266(QString cmd);

    /* 连接到云服务器 */
    void connectToClound();


signals:
public slots:
    /* 串口读消息 */
    void serialPortReadyRead();

    /* 串口发送消息 */
    void sendTextMessage(QString message);

    /* 定时器时间到，发送心跳包 */
    void onTimerTimeOut();
};
#endif // ESP82266_H
