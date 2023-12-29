#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>

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
signals:
    /* 声明一个信号，只需声明，无需定义 */
    void pushButtonTextChanged();

public slots:
    /* 声明一个槽函数 */
    void changeButtonText();

    /* 声明按钮点击的槽函数 */
    void pushButtonClicked();

private:
    /* 声明一个对象 pushButton */
    QPushButton *pushButton;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
