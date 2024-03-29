#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"
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
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void handleResults(const QString &results);

private:
    Ui::MainWindow *ui;

    /* 工人类 */
    Worker *worker;

    /* 全局线程 */
    QThread *workerThread;

signals:
    void startWork(QString str);
};
#endif // MAINWINDOW_H
