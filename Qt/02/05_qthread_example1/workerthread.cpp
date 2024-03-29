#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent)
{


}

void WorkerThread::run()
{
    QString result = "线程开启成功";
    qDebug() << "子线程：" << QThread::currentThreadId();
    QThread::sleep(2);
    emit resultReady(result);
}
