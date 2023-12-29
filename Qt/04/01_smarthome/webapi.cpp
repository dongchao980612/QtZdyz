#include "webapi.h"

Webapi::Webapi(QObject *parent) : QObject(parent)
{
    /* 数组清空 */
    m_groupID.clear();
    m_deviceID.clear();
    m_deviceNumber.clear();

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeOut()));

    m_networkAccessManager = new QNetworkAccessManager(this);

    m_orgURL = "https://cloud.alientek.com/api/orgs";
    /* 请填写自己的token信息！！！ */
    m_api_token = "4861531a9e1b41b4b11db8ad7888d50c";

    /* 获取账号机构列表 */
    getOrgURL();

    m_webSocket = new QWebSocket();
    /* 需要加一些安全配置才能访问https */
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    m_webSocket->setSslConfiguration(config);



}

void Webapi::getOrgURL()
{
    getDataFromWeb(QUrl(m_orgURL));
}

void Webapi::getGroupListUrl()
{
    getDataFromWeb(QUrl(m_devOfGroupUrl));
}

void Webapi::getDataFromWeb(QUrl url)
{
    qDebug()<<__FUNCTION__;
    /* 网络请求 */
    QNetworkRequest networkRequest;

    /* 需要加一些安全配置才能访问https */
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    networkRequest.setSslConfiguration(config);

    /* 设置访问的地址 */
    networkRequest.setUrl(url);

    /* 网络响应 */
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                                 "application/json;charset=UTF-8");

    /* 参数二为原子云帐号的token信息,填写自己的 */
    networkRequest.setRawHeader("token", m_api_token.toLatin1());

    QNetworkReply *newReply = m_networkAccessManager->get(networkRequest);
    // qDebug()<<newReply->error();

    connect(newReply, SIGNAL(finished()),
            this, SLOT(replyFinished()));
    connect(newReply, SIGNAL(readyRead()),
            this, SLOT(readyReadData()));
}

void Webapi::getID(QString data, QNetworkReply *reply)
{
    /* 多个匹配，因为可能有多个合适的字段 */
    QRegularExpression pattern("\"id\":(\\d+)");

    QRegularExpressionMatchIterator i = pattern.globalMatch(data);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            if (reply->url() == QUrl(m_orgURL)) {
                org_id =  match.captured(1);
                m_groupListUrl = "https://cloud.alientek.com/api/orgs/"+ org_id + "/grouplist";
                getGroupListUrl();
                /* Socket连接 */
                m_webSocket->open(QUrl(QString("wss://cloud.alientek.com/connection/%1/org/%2?token=%3").arg(m_api_token).arg(org_id).arg(m_random_token)));
            }

            if (reply->url() == QUrl(m_groupListUrl)) {
                m_group_id = match.captured(1);
                /* 存储组ID，再由定时器根据组的ID获取设备信息 */
                m_groupID.append(m_group_id);
                qDebug()<<"组ID:"<<m_group_id<<endl;

            }

            if (reply->url() == QUrl(m_devOfGroupUrl)) {
                m_device_id = match.captured(1);
                /* 存储设备ID,再由定时器根据设备的ID获取连接状态 */
                m_deviceID.append(m_device_id);
                qDebug()<<"设备ID:"<<m_device_id<<endl;
            }
        }
    }
}

void Webapi::getNumber(QString data)
{
    QRegularExpression pattern("\"number\":\"(\\d+)\"");

    QRegularExpressionMatchIterator i = pattern.globalMatch(data);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            m_device_number = match.captured(1);
            m_deviceNumber.append(m_device_number);
            qDebug()<<"设备编号："<<m_device_number<<endl;
        }
    }
}

void Webapi::getName(QString data)
{
    /* 匹配中文字符，设备起名需要为中文 */
    QRegularExpression pattern("\"name\":\"([\u4e00-\u9fa5]*)");

    QRegularExpressionMatchIterator i = pattern.globalMatch(data);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            m_device_name = match.captured(1);
            m_deviceName.append(m_device_name);
            qDebug()<<"设备名称："<<m_device_name<<endl;
        }
    }
}

void Webapi::getConnectState(QString data)
{
    QString pattern = "\"data\":\"(\\S*)\"";
    QRegularExpression regularExpression(pattern);
    QRegularExpressionMatch  match = regularExpression.match(data, 0);
    if(match.hasMatch()) {
        qDebug()<<"设备连接状态"<<match.captured(1);
        m_deviceConnectState.append(match.captured(1));
    }
}

void Webapi::sendCmdMessage(QString number, QByteArray cmd, QString message)
{

}

void Webapi::onTimerTimeOut()
{

}

void Webapi::replyFinished()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    qDebug()<<"replyFinished-->"<<reply->url();

    if (reply->url() == QUrl(m_orgURL)) {
        /* 设备分组列表ID */
        getID(m_dataString, reply);
    }

    if (reply->url() == QUrl(m_groupListUrl)) {
        /* 列表ID */
        getID(m_dataString, reply);

    /* 获取到组ID再开启定时器 */
    if (!m_timer->isActive())
        m_timer->start(2000);
    }

    /* 设备的信息 */
    if (reply->url() == QUrl(m_devOfGroupUrl)) {
        getID(m_dataString, reply);
        getNumber(m_dataString);
        getName(m_dataString);
    }

    /* 设备的连接状态 */
    if (reply->url() == QUrl(m_conStateUrl)) {
        getConnectState(m_dataString);
    }

    reply->deleteLater();
    reply = nullptr;
}

void Webapi::readyReadData()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    QByteArray data = reply->readAll();
    m_dataString =  QString(data);
    qDebug()<<"readyReadData-->"<<m_dataString<<endl;
}

void Webapi::webSocketConnected()
{
    qDebug()<<"webSocket连接原子云成功"<<endl;
}

void Webapi::onBinaryMessageReceived(QByteArray str)
{
    QString temp(str);
    if (temp.contains("online")) {
        for (int i = 0; i < m_deviceNumber.count() ; i++) {
            if (temp.contains(m_deviceNumber[i])) {
                /* 发送如客厅灯在线信号*/
                emit deviceStateChanged(m_deviceName[i] + "|在线");
                qDebug()<<m_deviceName[i] + "|在线"<<endl;
                break;
            }
        }
    }
}

void Webapi::whichDeviceNameSendCmd(QString name, QString message)
{
    for (int i = 0; i < m_deviceName.count(); i++)
    {
        if (name ==  m_deviceName[i]) {
            QByteArray cmd;
            cmd[0] = 0x03;
            sendCmdMessage(m_deviceNumber[i], cmd, message);
            break;
        }
    }
}
