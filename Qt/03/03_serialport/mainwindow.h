#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include<QSerialPortInfo>

#include <QMessageBox>
#include <QComboBox>

#include <QDebug>

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


    void on_pushButtonSend_clicked();

    void on_pushButtonOpen_clicked();

private:
    Ui::MainWindow *ui;

    /* 串口对象 */
    QSerialPort *serialPort;

    /* 布局初始化 */
    void layoutInit();

    /* 扫描系统可用串口 */
    void scanSerialPort();

    /* 波特率项初始化 */
    void baudRateItemInit();

    /* 数据位项初始化 */
    void dataBitsItemInit();

    /* 检验位项初始化 */
    void parityItemInit();

    /* 停止位项初始化 */
    void stopBitsItemInit();

    QList <QComboBox *> comboBoxList;

};
#endif // MAINWINDOW_H
