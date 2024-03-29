#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);

    /* 布局初始化 */
    layoutInit();

    /* 扫描系统的串口 */
    scanSerialPort();

    /* 波特率项初始化 */
    baudRateItemInit();

    /* 数据位项初始化 */
    dataBitsItemInit();

    /* 检验位项初始化 */
    parityItemInit();

    /* 停止位项初始化 */
    stopBitsItemInit();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::layoutInit()
{
    QList <QScreen *> list_screen = QGuiApplication::screens();

    /* 如果是ARM平台，直接设置大小为屏幕的大小 */
#if __arm__
    /* 重设大小 */
    this->resize(list_screen.at(0)->geometry().width(),  list_screen.at(0)->geometry().height());
#else
    {
        /* 否则则设置主窗体大小为800x480 */
        this->resize(800, 480);
    }
#endif
    QList <QLabel *> labelList;
    labelList << ui->labelPort << ui->labelRate << ui->labelData << ui->labelCheck << ui->labelStop;
    foreach(auto label, labelList)
    {
        label->setMinimumSize(80, 30);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // QList <QComboBox *>comboBoxList;
    comboBoxList << ui->comboBoxPort << ui->comboBoxRate << ui->comboBoxData << ui->comboBoxCheck << ui->comboBoxStop;
    foreach(auto comboBox, comboBoxList)
    {
        comboBox->setMinimumSize(80, 30);
        comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    QList <QPushButton *> buttonList;
    buttonList << ui->pushButtonOpen << ui->pushButtonSend;
    foreach(auto button, buttonList)
    {
        button->setMinimumSize(80, 30);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    /* 占位文本 */
    ui->textBrowser->setPlaceholderText("接收到的消息");
    ui->textEdit->setPlaceholderText("请输入信息...");
}

void MainWindow::scanSerialPort()
{

    /* 查找可用串口 */
    QList<QSerialPortInfo> availablePortsList = QSerialPortInfo::availablePorts();
    qDebug() << availablePortsList.size();

    foreach (const QSerialPortInfo &info,  availablePortsList)
    {
        ui->comboBoxPort->addItem(info.portName());
    }
}

void MainWindow::baudRateItemInit()
{
    /* QList链表，字符串类型 */
    QList <QString> list;
    list << "1200" << "2400" << "4800" << "9600"  << "19200" << "38400" << "57600"  << "115200" << "230400" << "460800"  << "921600";
    for (int i = 0; i < 11; i++)
    {
        ui->comboBoxRate->addItem(list[i]);
    }
    ui->comboBoxRate->setCurrentIndex(7);
}

void MainWindow::dataBitsItemInit()
{
    /* QList链表，字符串类型 */  QList <QString> list;
    list << "5" << "6" << "7" << "8";
    for (int i = 0; i < 4; i++)
    {
        ui->comboBoxData->addItem(list[i]);
    }
    ui->comboBoxData->setCurrentIndex(3);
}

void MainWindow::parityItemInit()
{
    /* QList链表，字符串类型 */
    QList <QString> list;
    list << "None" << "Even" << "Odd" << "Space" << "Mark";
    for (int i = 0; i < 5; i++)
    {
        ui->comboBoxCheck->addItem(list[i]);
    }
    ui->comboBoxCheck->setCurrentIndex(0);
}

void MainWindow::stopBitsItemInit()
{
    /* QList链表，字符串类型 */  QList <QString> list;
    list << "1" << "2";
    for (int i = 0; i < 2; i++)
    {
        ui->comboBoxStop->addItem(list[i]);
    }
    ui->comboBoxStop->setCurrentIndex(0);
}


void MainWindow::on_pushButtonSend_clicked()
{
    /* 获取textEdit数据,转换成utf8格式的字节流 */
    QByteArray data = ui->textEdit->toPlainText().toUtf8();
    serialPort->write(data);
}

void MainWindow::on_pushButtonOpen_clicked()
{
    if(ui->pushButtonOpen->text() == "打开串口")
    {

        /* 设置串口名 */
        serialPort->setPortName(ui->comboBoxPort-> currentText());

        /* 设置波特率 */
        serialPort->setBaudRate(ui->comboBoxRate->currentText().toInt());

        /* 设置数据位数 */
        switch (ui->comboBoxData->currentText().toInt())
        {
            case 5:
                serialPort->setDataBits(QSerialPort::Data5);
                break;
            case 6:
                serialPort->setDataBits(QSerialPort::Data6);
                break;
            case 7:
                serialPort->setDataBits(QSerialPort::Data7);
                break;
            case 8:
                serialPort->setDataBits(QSerialPort::Data8);
                break;
            default:
                break;
        }

        /* 设置奇偶校验 */
        switch (ui->comboBoxCheck->currentIndex())
        {
            case 0:
                serialPort->setParity(QSerialPort::NoParity);
                break;
            case 1:
                serialPort->setParity(QSerialPort::EvenParity);
                break;
            case 2:
                serialPort->setParity(QSerialPort::OddParity);
                break;
            case 3:
                serialPort->setParity(QSerialPort::SpaceParity);
                break;
            case 4:
                serialPort->setParity(QSerialPort::MarkParity);
                break;
            default:
                break;

        }
        /* 设置停止位 */
        switch (ui->comboBoxStop->currentText().toInt())
        {
            case 1:
                serialPort->setStopBits(QSerialPort::OneStop);
                break;
            case 2:
                serialPort->setStopBits(QSerialPort::TwoStop);
                break;
            default:
                break;
        }

        /* 设置流控制 */
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        if (!serialPort->open(QIODevice::ReadWrite))
        {
            QMessageBox::about(this, "错误",  "串口无法打开！可能串口已经被占用！");
        }
        else
        {
            for (int i = 0; i < 5; i++)
            {
                comboBoxList[i]->setEnabled(false);
            }
            ui->pushButtonOpen->setText("关闭串口");
            ui->pushButtonSend->setEnabled(true);

        }
    }
    else
    {
        serialPort->close();
        for (int i = 0; i < 5; i++)
        {
            comboBoxList[i]->setEnabled(true);
        }
        ui->pushButtonOpen->setText("打开串口");
        ui->pushButtonSend->setEnabled(false);
    }

}
