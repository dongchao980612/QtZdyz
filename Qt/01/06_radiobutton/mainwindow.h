#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/* 引入QRadioButton */
#include <QRadioButton>
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

private:
    Ui::MainWindow *ui;
    /* 声明两个QRadioButton对象 */
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
};
#endif // MAINWINDOW_H
