#include "esp82266.h"

Esp82266::Esp82266(QObject *parent) : QObject(parent)
{
#if 0
    QList<QSerialPortInfo>  postList = QSerialPortInfo::availablePorts();
    qDebug()<<postList.size();
    for(int i =0;i<postList.size();i++){
        qDebug()<<"i = "<<postList.at(i).portName();
    }
#endif
    /* 串口对象，用于与Esp8266模块通信 */
    m_serialPort = new QSerialPort(this);
    /* 设置串口名 */
 #if __arm__
     m_serialPort->setPortName("ttySTM2");
 #else
     m_serialPort->setPortName("ttyACM1");
 #endif

    /* 设置波特率 */
    m_serialPort->setBaudRate(115200);

    /* 设置数据位数 */
    m_serialPort->setDataBits(QSerialPort::Data8);

    /* 设置奇偶校验 */
    m_serialPort->setParity(QSerialPort::NoParity);

    /* 设置停止位 */
    m_serialPort->setStopBits(QSerialPort::OneStop);

    /* 设置流控制 */
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serialPort->open(QIODevice::ReadWrite))
    {
        qDebug()<<"串口无法打开！可能正在被使用！"<<endl;
    }
    else
    {
        qDebug()<<"串口打开成功！"<<endl;
    }


    /* 定时器对象，用于定时发送设备在线的心跳包 */
    m_timer = new QTimer();

    /* 开始连接云 */
    connectToClound();

    connect(m_serialPort, SIGNAL(readyRead()),this, SLOT(serialPortReadyRead()));

    connect(m_timer, SIGNAL(timeout()),this, SLOT(onTimerTimeOut()));

}

void Esp82266::serialPortReadyRead()
{
    // qDebug()<<__FUNCTION__;
    QByteArray buf = m_serialPort->readAll();

    QString temp = QString(buf);
    m_readData.append(temp);
    qDebug()<<temp<<endl;

    if  (m_readData.contains("ready"))
    {
        /* 如果复位成功 */
        sendCmdToEsp8266("AT+CWMODE=1");
        m_readData.clear();
    }

    if (m_readData.contains("OK") && m_readData.contains("AT+CWMODE"))
    {
        qDebug()<<"设置STA模式成功"<<endl;
        sendCmdToEsp8266("AT+CWJAP=\"Xiaomi14\",\"Dd123912@\"");
        qDebug()<<"开始连接WIFI"<<endl;
        m_readData.clear();
    }

    if  (temp.contains("WIFI GOT"))
    {
        /* WIFI GOT IP */
        qDebug()<<"连接WIFI成功"<<endl;
        sleep(2);
        /* 原子云的设备号及密码 */
        sendCmdToEsp8266("AT+ATKCLDSTA=\"74036168866902521409\",\"12345678\"");
        qDebug()<<"开始连接原子云请等待"<<endl;
    }

    if (temp.contains("CLOUD CO"))
    {     /* CLOUD CONNECTED */
        qDebug()<<"连接原子云成功"<<endl;
        sleep(2);
        /* 15s就发送一次心跳包 */
        m_timer->start(15000);
    }

}

void Esp82266::sendTextMessage(QString message)
{
    m_serialPort->write(message.toLatin1());
}

void Esp82266::onTimerTimeOut()
{
    sendTextMessage("online");
    qDebug()<<"发送设备在线心跳包"<<endl;
}
Esp82266::~Esp82266()
{
    m_serialPort->close();
    delete m_timer;
    m_timer = nullptr;
}

void Esp82266::sendCmdToEsp8266(QString cmd)
{
    cmd = cmd + "\r\n";
    QByteArray data = cmd.toUtf8();
    m_serialPort->write(data);
}

void Esp82266::connectToClound()
{
    /* 重启模块，注意若已经连接上原子云，
     * 需要重新上电或者短接RST脚来复位模块 */
    sendCmdToEsp8266("AT+RST");
}
void Esp82266::sleep(int second)
{
    usleep(second * 1000000);
}
