#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTimeEdit>
#include <QTimeEdit>
#include <QDateEdit>
#include <QDebug>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /* 声明对象 */
    QDateTimeEdit *dateTimeEdit;
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;

private slots:
    void dateTimeEditDateTimeChanged(const QDateTime &dateTime);
    void dateEditDateChanged(const QDate &date);
    void timeEditTimeChanged(const QTime &time);
};
#endif // MAINWINDOW_H
