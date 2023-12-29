#ifndef WEBAPI_H
#define WEBAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebSocket>
#include <unistd.h>
#include <QTimer>
#include <QUuid>
#include <QRegularExpression>
class Webapi : public QObject
{
    Q_OBJECT
public:
    explicit Webapi(QObject *parent = nullptr);

    QTimer *m_timer;

    QString m_api_token;
    QString m_random_token;

    void sleep(double second);

    QVector<QString> m_groupID;
    QVector<QString> m_deviceID;
    QVector<QString> m_deviceNumber;
    QVector<QString> m_deviceName;
    QVector<QString> m_deviceConnectState;

    // HTTPS
    QNetworkAccessManager *m_networkAccessManager;

    /* 返回的字符串信息 */
    QString m_dataString;

    /* 账号机构列表id */
    QString org_id;

    /* 分组id */
    QString m_group_id;

    /* 设备id */
    QString m_device_id;

    /* 设备编号 */
    QString m_device_number;

    /* 设备名字（非必须，设计时为了匹配控制面板里的控制项）*/
    QString m_device_name;

    /* 原子云连接URL */
    QString m_orgURL;

    /* 设备分组URL*/
    QString m_groupListUrl;

    /* 分组下的URL */
    QString m_devOfGroupUrl;

    /* 连接状态URL */
    QString m_conStateUrl;

    /* 获取账号机构列表 */
    void getOrgURL();

    /* 获取分组列表 */
    void getGroupListUrl();

    /* 获取分组列表下的设备 */
    void getDevOfGroupUrl();

    /* 获取设备的连接状态 */
    void getConStateUrl();



    /* 网络返回的数据 */
    void getDataFromWeb(QUrl url);

    /* 获取id */
    void getID(QString id , QNetworkReply *reply);

    /* 获取设备编号 */
    void getNumber(QString data);

    /* 获取设备名字 */
    void getName(QString data);

    /* 获取设备的连接状态 */
    void getConnectState(QString data);

    // WebSocket
    QWebSocket *m_webSocket;

    /* 发送命令/发送命令+消息 */
    void sendCmd(QString number, QByteArray cmd);
    void sendCmdMessage(QString number, QByteArray cmd, QString message);

private slots:

    void onTimerTimeOut();

    // HTTPS
    void replyFinished();
    void readyReadData();

    // WebSocket
    void webSocketConnected();
    void onBinaryMessageReceived(QByteArray ba);

public:
    void whichDeviceNameSendCmd(QString name, QString message);

signals:
    void deviceStateChanged(QString deviceState);

};

#endif // WEBAPI_H
