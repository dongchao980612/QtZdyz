#include "led.h"

Led::Led(QObject *parent) : QObject(parent)
{
    this->setParent(parent);
#if __arm__
    /* 默认是出厂系统的LED心跳的触发方式,想要控制LED，
     * 需要改变LED的触发方式，改为none，即无 */
    system("echo none > /sys/class/leds/sys-led/trigger");
#endif
    // 开发板的LED控制接口
    m_file.setFileName("/sys/devices/platform/leds/leds/sys-led/brightness");

}
void Led::setLedState(bool flag){
    qDebug()<<flag<<endl;

    // 如果文件不存在，则返回
    if (!m_file.exists())
     {
           return;
    }

    if(!m_file.open(QIODevice::ReadWrite))
    {
        qDebug()<<m_file.errorString();
    }

    QByteArray buf[2] = {"0", "1"};

    // 写0或1,1~255都可以点亮LED
    if (flag)
    {
        m_file.write(buf[1]);
    }
    else
    {
        m_file.write(buf[0]);
    }

    // 关闭文件
    m_file.close();
}
