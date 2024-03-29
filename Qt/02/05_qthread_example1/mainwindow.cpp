#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_workerThread = new WorkerThread(this);
    /* 按钮设置大小与文本 */
    ui->pushButton->resize(100, 40);
    ui->pushButton->setText("开启线程");
    qDebug() << "主线程：" << QThread::currentThreadId();

    connect(m_workerThread, SIGNAL(resultReady(QString)),  this, SLOT(handleResults(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    /* 进程退出，注意本例run()方法没写循环，此方法需要有循环才生效 */
    m_workerThread->quit();

    /* 阻塞等待2000ms检查一次进程是否已经退出 */
    if (m_workerThread->wait(2000))
    {
        qDebug() << "线程已经结束！" << endl;
    }
}


void MainWindow::on_pushButton_clicked()

{
    qDebug() << __FUNCTION__ << endl;
    /* 信号槽连接 */

    /* 检查线程是否在运行，如果没有则开始运行 */
    if (!m_workerThread->isRunning())
    {
        m_workerThread->start();
    }
}


void MainWindow::handleResults(const QString &result)
{
    /* 打印出线程发送过来的结果 */
    qDebug() << result << endl;

}
