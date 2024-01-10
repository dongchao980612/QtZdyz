#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpServer>
#include <QTcpSocket>

#include <QHostInfo>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

#include <QDebug>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    /* 开始监听槽函数 */
    void startListen();

    /* 停止监听槽函数 */
    void stopListen();

    /* 清除文本框时的内容 */
    void clearTextBrowser();

    /* 发送消息 */
    void sendMessages();

    /* 客户端连接处理槽函数 */
    void clientConnected();

    /* 接收到消息 */
    void receiveMessages();

    /* 连接状态改变槽函数 */
    void socketStateChange(QAbstractSocket::SocketState);

private:
    Ui::MainWindow *ui;
private:
    /* tcp服务器 */
    QTcpServer *tcpServer;

    /* 通信套接字 */
    QTcpSocket *tcpSocket;

    /* 存储本地的ip列表地址 */
    // QList<QHostAddress> IPlist;

    void getLocalHostIP();
};
#endif // MAINWINDOW_H
