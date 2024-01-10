#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("tcp服务器");

    /* 设置主窗体的位置与大小 */
    this->setMaximumSize(800, 480);
    this->setMinimumSize(800, 480);

    tcpServer = NULL;
    tcpSocket = NULL;


    /* 实例化tcp服务器与tcp套接字 */
    tcpServer = new QTcpServer(this);
    // tcpSocket = new QTcpSocket(this);


    /* 设置标签根据文本文字大小自适应大小 */
    ui->labelIP->setSizePolicy(QSizePolicy::Fixed,  QSizePolicy::Fixed);
    ui->labelPort->setSizePolicy(QSizePolicy::Fixed,  QSizePolicy::Fixed);


    /* 设置端口号的范围，注意不要与主机的已使用的端口号冲突 */
    ui->spinBoxPort->setRange(10000, 99999);

    /* 设置停止监听状态不可用 */
    ui->pushButtonStop->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);

    /* 设置输入框默认的文本 */
    ui->lineEdit->clear();
    ui->lineEdit->setPlaceholderText("请输入信息...");

    /* 获取本地ip */
    getLocalHostIP();


    /* 信号槽连接 */
    connect(ui->pushButtonBegin, &QPushButton::clicked,  this, &MainWindow::startListen);
    connect(ui->pushButtonStop, &QPushButton::clicked,  this, &MainWindow::stopListen);
    connect(ui->pushButtonClear, &QPushButton::clicked,  this, &MainWindow::clearTextBrowser);
    connect(ui->pushButtonSend, &QPushButton::clicked,  this, &MainWindow::sendMessages);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* 开始监听 */
void MainWindow::startListen()
{
    qDebug() << __FUNCTION__;
    /* 需要判断当前主机是否有IP项 */
    if (ui->comboBoxIP->currentIndex() != -1)
    {
        tcpServer->listen(QHostAddress(ui->comboBoxIP->currentText()), ui->spinBoxPort->value());

        /* 设置按钮与下拉列表框的状态 */
        ui->pushButtonBegin->setEnabled(false);
        ui->pushButtonStop->setEnabled(true);
        ui->comboBoxIP->setEnabled(false);
        ui->spinBoxPort->setEnabled(false);

        /* 在文本浏览框里显示出服务端 */
        ui->textBrowser->append("服务器IP地址："  + ui->comboBoxIP->currentText());
        ui->textBrowser->append("正在监听端口："  + ui->spinBoxPort->text());

        connect(tcpServer, &QTcpServer::newConnection,  this, &MainWindow::clientConnected);
    }
}

void MainWindow::stopListen()
{
    qDebug() << __FUNCTION__;

    ui->lineEdit->clear();
    ui->lineEdit->setPlaceholderText("请输入信息...");
    ui->pushButtonSend->setEnabled(false);


    /* 停止监听 */
    if (tcpSocket->state() == tcpSocket->ConnectedState)
    {
        tcpSocket->disconnectFromHost();
        tcpSocket->disconnect();
        tcpServer->disconnect();
        tcpServer->close();
    }

    /* 设置按钮与下拉列表框的状态 */
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonBegin->setEnabled(true);

    ui->comboBoxIP->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
    ui->lineEdit->setEnabled(false);


    /* 将停止监听的信息添加到文本浏览框中 */
    ui->textBrowser->append("已停止监听端口：" + ui->spinBoxPort->text());
}

/* 清除文本浏览框里的内容 */
void MainWindow::clearTextBrowser()
{
    qDebug() << __FUNCTION__;
    /* 清除文本浏览器的内容 */
    ui->textBrowser->clear();
}

void MainWindow::sendMessages()
{
    qDebug() << __FUNCTION__;
    if(NULL == tcpSocket)
    {
        return;
    }
    /* 如果已经连接 */
    if(tcpSocket->state() == tcpSocket->ConnectedState)
    {
        /* 发送消息 */
        tcpSocket->write(ui->lineEdit->text().toUtf8().data());
        /* 在服务端插入发送的消息 */
        ui->textBrowser->append("服务端：" + ui->lineEdit->text());
        ui->lineEdit->clear();
        ui->lineEdit->setPlaceholderText("请输入信息...");
    }
    else
    {
        return;
    }
}

/* 新的客户端连接 */
void MainWindow::clientConnected()
{
    qDebug() << __FUNCTION__;
    ui->lineEdit->setEnabled(true);
    ui->pushButtonSend->setEnabled(true);

    QMessageBox::information(this, "提示", "客户端连接");
    /* 获取客户端的套接字 */
    tcpSocket = tcpServer->nextPendingConnection(); // 相当于new出来一个指针

    /* 客户端的ip信息 */
    QString ip = tcpSocket->peerAddress().toString();
    /* 客户端的端口信息 */
    quint16 port = tcpSocket->peerPort();

    /* 在文本浏览框里显示出客户端的连接信息 */
    ui->textBrowser->append("客户端已连接");
    ui->textBrowser->append("客户端ip地址:"  + ip);
    ui->textBrowser->append("客户端端口:"  + QString::number(port));

    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::receiveMessages);
    connect(tcpSocket,  &QTcpSocket::stateChanged, this, &MainWindow::socketStateChange);
}

/* 接收到消息 */
void MainWindow::receiveMessages()
{
    qDebug() << __FUNCTION__;
    QString data = "客户端：" + tcpSocket->readAll();
    ui->textBrowser->append(data);
}

/* 连接状态改变槽函数 */
void MainWindow::socketStateChange(QAbstractSocket::SocketState state)
{
    qDebug() << __FUNCTION__;
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
    qDebug() << __FUNCTION__;
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
            }
        }
    }
}

