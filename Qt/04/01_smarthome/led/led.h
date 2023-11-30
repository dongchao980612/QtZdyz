#ifndef LED_H
#define LED_H

#include <QObject>
#include <QFile>
class Led : public QObject
{
    Q_OBJECT

public:
    Led(QObject *parent = nullptr);
    ~Led();

    /* 设置lED的状态 */
    void setLedState(bool);

private:
    /* 文件 */
    QFile file;
};
#endif // LED_H
