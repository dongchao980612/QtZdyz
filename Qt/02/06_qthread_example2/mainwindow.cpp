#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton1->setText("开启线程");
    ui->pushButton2->setText("打断线程");

    /* 工人类实例化 */
    worker = new Worker;
    /* 将worker类移至线程workerThread */
    workerThread = new QThread(this);

    /* 将worker类移至线程workerThread */
    worker->moveToThread(workerThread);

    /* 信号槽连接 */

    /* 线程完成销毁对象 */
    connect(workerThread, SIGNAL(finished()),  worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()),  workerThread, SLOT(deleteLater()));

    /* 发送开始工作的信号，开始工作 */
    connect(this, SIGNAL(startWork(QString)), worker, SLOT(doWork1(QString)));

    /* 接收到worker发送过来的信号 */
    connect(worker, SIGNAL(resultReady(QString)),  this, SLOT(handleResults(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
    /* 打断线程再退出 */
    worker->stopWork();
    workerThread->quit();

    /* 阻塞线程2000ms，判断线程是否结束 */
    if (workerThread->wait(2000))
    {
        qDebug() << "线程结束" << endl;
    }

}
void MainWindow::on_pushButton1_clicked()
{
    /* 字符串常量 */
    const QString str = "正在运行";

    /* 判断线程是否在运行 */
    if(!workerThread->isRunning())
    {
        /* 开启线程 */
        workerThread->start();
    }

    /* 发送正在运行的信号，线程收到信号后执行后返回线程耗时函数 + 此字符串 */
    emit this->startWork(str);
}

void MainWindow::on_pushButton2_clicked()
{
    /* 如果线程在运行 */
    if(workerThread->isRunning())
    {
        /* 停止耗时工作，跳出耗时工作的循环 */
        worker->stopWork();
    }
}


void MainWindow::handleResults(const QString &results)
{
    /* 打印线程的状态 */
    qDebug() << "线程的状态：" << results << endl;
}
