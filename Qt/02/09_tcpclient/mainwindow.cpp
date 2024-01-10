#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("tcp客户端");

    /* 设置主窗体的位置与大小 */
    this->setGeometry(0, 0, 800, 480);
    this->setMaximumSize(800, 480);
    this->setMinimumSize(800, 480);

    /* tcp套接字 */
    tcpSocket = new QTcpSocket(this);

    /* 设置标签根据文本文字大小自适应大小 */
    ui->labelIP->setSizePolicy(QSizePolicy::Fixed,  QSizePolicy::Fixed);
    ui->labelPort->setSizePolicy(QSizePolicy::Fixed,  QSizePolicy::Fixed);


    /* 设置端口号的范围，注意不要与主机的已使用的端口号冲突 */
    ui->spinBoxPort->setRange(10000, 99999);

    /* 设置停止监听状态不可用 */
    ui->pushButtonDisConnet -> setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);

    /* 设置输入框默认的文本 */
    ui->lineEdit->clear();
    ui->lineEdit->setPlaceholderText("请输入信息...");

    /* 获取本地ip */
    getLocalHostIP();

    /* 信号槽连接 */
    connect(ui->pushButtonConnect, &QPushButton::clicked,  this, &MainWindow::toConnect);
    connect(ui->pushButtonDisConnet, &QPushButton::clicked,  this, &MainWindow::toDisConnect);
    connect(ui->pushButtonClear, &QPushButton::clicked,  this, &MainWindow::clearTextBrowser);
    connect(ui->pushButtonSend, &QPushButton::clicked,  this, &MainWindow::sendMessages);


}

MainWindow::~MainWindow()
{
    delete ui;
}

/* 连接 */
void MainWindow::toConnect()
{
    if(NULL == tcpSocket)
    {
        return ;
    }
    /* 如果连接状态还没有连接 */
    if (tcpSocket->state() != tcpSocket->ConnectedState)
    {
        /* 指定IP地址和端口连接 */
        tcpSocket->connectToHost(ui->comboBoxIP->currentText(),  ui->spinBoxPort->value());
        qDebug() << __FUNCTION__;
        connect(tcpSocket, &QTcpSocket::connected,  this, &MainWindow::connected);
        connect(tcpSocket, &QTcpSocket::disconnected,  this, &MainWindow::disconnected);
        connect(tcpSocket, &QTcpSocket::readyRead,  this, &MainWindow::receiveMessages);
        connect(tcpSocket,  &QTcpSocket::stateChanged, this,   &MainWindow::socketStateChange);
    }
}

/* 断开连接 */
void MainWindow::toDisConnect()
{
    if(NULL == tcpSocket)
    {
        return ;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

}

/* 清除文本框时的内容 */
void MainWindow::clearTextBrowser()
{
    /* 清除文本浏览器的内容 */
    ui->textBrowser->clear();
}

/* 接收消息 */
void MainWindow::receiveMessages()
{
    /* 读取接收到的消息 */
    QString messages = tcpSocket->readAll();
    ui->textBrowser->append("服务端：" + messages);
}

/* 发送消息 */
void MainWindow::sendMessages()
{
    if(NULL == tcpSocket)
    {
        return;
    }

    if(tcpSocket->state() == tcpSocket->ConnectedState)
    {
        /* 客户端显示发送的消息 */
        ui->textBrowser->append("客户端：" + ui->lineEdit->text());

        /* 发送消息 */
        tcpSocket->write(ui->lineEdit->text().toUtf8().data());

    }

}

/* 已连接 */
void MainWindow::connected()
{
    /* 显示已经连接 */
    ui->textBrowser->append("已经连上服务端");
    /* 设置按钮与下拉列表框的状态 */
    ui->lineEdit->setEnabled(true);
    ui->pushButtonSend->setEnabled(true);
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonDisConnet->setEnabled(true);
    ui->comboBoxIP->setEnabled(false);
    ui-> spinBoxPort->setEnabled(false);
}

/* 已断开连接 */
void MainWindow::disconnected()
{
    /* 显示已经断开连接 */
    ui->textBrowser->append("已经断开服务端");
    /* 设置按钮与下拉列表框的状态 */
    ui->lineEdit->clear();
    ui->lineEdit->setPlaceholderText("请输入信息...");
    ui->pushButtonDisConnet->setEnabled(false);
    ui->pushButtonConnect->setEnabled(true);
    ui->comboBoxIP->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
}

/* 连接状态改变槽函数 */
void MainWindow::socketStateChange(QAbstractSocket::SocketState state)
{
    ui->pushButtonSend->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    switch (state)
    {
        case QAbstractSocket::UnconnectedState:
            ui->textBrowser->append("scoket状态：UnconnectedState");
            break;
        case QAbstractSocket::ConnectedState:
            ui->textBrowser->append("scoket状态：ConnectedState");
            break;
        case QAbstractSocket::ConnectingState:
            ui->textBrowser->append("scoket状态：ConnectingState");
            break;
        case QAbstractSocket::HostLookupState:
            ui->textBrowser->append("scoket状态：HostLookupState");
            break;
        case QAbstractSocket::ClosingState:
            ui->textBrowser->append("scoket状态：ClosingState");
            break;
        case QAbstractSocket::ListeningState:
            ui->textBrowser->append("scoket状态：ListeningState");
            break;
        case QAbstractSocket::BoundState:
            ui->textBrowser->append("scoket状态：BoundState");
            break;
        default:
            break;

    }
}

void MainWindow::getLocalHostIP()
{
    /* 获取所有的网络接口, QNetworkInterface类提供主机的IP地址和网络接口的列表 */
    QList<QNetworkInterface> list  = QNetworkInterface::allInterfaces();

    /* 遍历list */
    foreach(QNetworkInterface interface, list)
    {
        /* QNetworkAddressEntry类存储IP地址子网掩码和广播地址 */
        QList<QNetworkAddressEntry> entryList  = interface.addressEntries();

        /* 遍历entryList */
        foreach (QNetworkAddressEntry addressEntry, entryList)
        {
            if (addressEntry.ip().protocol() ==  QAbstractSocket::IPv4Protocol)
            {
                ui->comboBoxIP->addItem(addressEntry.ip().toString());

                /* 添加到IP列表中 */
                // IPlist << addressEntry.ip();
            }
        }
    }
}

