#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QDebug>

/* 新建一个WorkerThread类继承于QThread */
class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = nullptr);
    void run() override;
signals:
    /* 声明一个信号，译结果准确好的信号 */
    void resultReady(const QString &s);

};

#endif // WORKERTHREAD_H
