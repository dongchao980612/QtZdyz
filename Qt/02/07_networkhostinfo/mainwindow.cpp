#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 设置位置与大小 */
    this->setGeometry(0, 0, 800, 480);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getHostInfo()
{
    QString str = "主机名称:" + QHostInfo::localHostName() + "\n";
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    foreach(QNetworkInterface interface, list)
    {
        str += "\t\t网卡设备" + interface.name() + "\n";
        str += "\t\tMAC地址" + interface.hardwareAddress() + "\n";
        QList<QNetworkAddressEntry> entryList  = interface.addressEntries();

        foreach(QNetworkAddressEntry addressEntry, entryList)
        {
            if (addressEntry.ip().protocol() ==  QAbstractSocket::IPv4Protocol)
            {
#if 0
                str += "\t\t\tIP4 地址:" + addressEntry.ip().toString() + "\n";
                str += "\t\t\t子网掩码:" + addressEntry.netmask().toString() + "\n";
                str += "\t\t\t广播地址:" + addressEntry.broadcast().toString() + "\n\n";
#endif
            }
            else if(addressEntry.ip().protocol() ==  QAbstractSocket::IPv6Protocol)
            {
#if 1
                str += "\t\t\tIP6 地址:" + addressEntry.ip().toString() + "\n";
                str += "\t\t\t子网掩码:" + addressEntry.netmask().toString() + "\n";
                str += "\t\t\t广播地址:" + addressEntry.broadcast().toString() + "\n\n";
#endif
            }
        }

    }

    return str;
}
void MainWindow::on_pushButton_GetInfo_clicked()
{

    QString hostInfoStr = getHostInfo();
    ui->textBrowser->insertPlainText(hostInfoStr);
}

void MainWindow::on_pushButton_Clear_clicked()
{
    if(!ui->textBrowser->toPlainText().isEmpty())
    {
        ui->textBrowser->clear();
    }
}
