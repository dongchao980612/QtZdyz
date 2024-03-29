#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QDebug>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

    /* 打断线程（注意此方法不能放在槽函数下） */
    void stopWork();

    /* 互斥锁 */
    QMutex lock;

    /* 标志位 */
    bool isCanRun;
signals:
    /* 工人工作函数状态的信号 */
    void resultReady(const QString &result);

public slots:

    void doWork1(const QString &parameter);
};

#endif // WORKER_H
