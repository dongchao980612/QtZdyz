#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::stopWork()
{
    qDebug() << "打断线程" ;

    /* 获取锁后，运行完成后即解锁 */
    QMutexLocker locker(&lock);
    isCanRun = false;
}

void Worker::doWork1(const QString &parameter)
{
    /* 标志位为真 */
    isCanRun = true;

    /* 死循环 */
    while (1)
    {
        /* 此{}作用是QMutexLocker与lock的作用范围，获取锁后，运行完成后即解锁 */
        {
            QMutexLocker locker(&lock);
            /* 如果标志位不为真 */
            if (!isCanRun)
            {
                /* 跳出循环 */
                break;
            }
        }
        /* 使用QThread里的延时函数，当作一个普通延时 */
        QThread::sleep(2);
        emit resultReady(parameter + __FUNCTION__);

    }
    /* doWork1运行完成，发送信号 */
    emit resultReady("打断doWork1函数");
}

