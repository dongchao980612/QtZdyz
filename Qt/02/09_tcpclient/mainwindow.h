#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpSocket>

#include <QHostInfo>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>


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
    /* 连接 */
    void toConnect();

    /* 断开连接 */
    void toDisConnect();

    /* 清除文本框时的内容 */
    void clearTextBrowser();

    /* 接受消息 */
    void receiveMessages();

    /* 发送消息 */
    void sendMessages();

    /* 已连接 */
    void connected();

    /* 已断开连接 */
    void disconnected();

    /* 连接状态改变槽函数 */
    void socketStateChange(QAbstractSocket::SocketState state);

private:
    Ui::MainWindow *ui;

    /* 通信套接字 */
    QTcpSocket *tcpSocket;

    /* 存储本地的ip列表地址 */
    // QList<QHostAddress> IPlist;

    /* 获取本地的所有ip */
    void getLocalHostIP();
};
#endif // MAINWINDOW_H
