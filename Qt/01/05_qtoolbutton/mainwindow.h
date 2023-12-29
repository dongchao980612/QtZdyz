#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/* 引入QToolButton类 */
#include <QToolButton>
/* 引入QToolBar类 */
#include <QToolBar>
/* 引入QStyle类 */
#include <QStyle>
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
    /* 声明一个QToolButton对象 */
    QToolButton *toolButton;
    /* 声明一个QToolBar对象 */
    QToolBar *toolBar;
};
#endif // MAINWINDOW_H
