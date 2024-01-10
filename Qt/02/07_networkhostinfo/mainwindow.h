#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void on_pushButton_GetInfo_clicked();

    void on_pushButton_Clear_clicked();

private:
    Ui::MainWindow *ui;
    QString getHostInfo();
};
#endif // MAINWINDOW_H
