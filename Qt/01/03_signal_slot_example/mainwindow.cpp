#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 设置窗体的宽为800,高为480 */
    this->resize(800, 480);

    /* 实例化pushButton对象 */
    pushButton = new QPushButton(this);

    /* 调用setText()方法设定按钮的文本 */
    pushButton->setText("我是一个按钮");

    /* 信号与槽连接 */
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::pushButtonClicked);
    connect(this,  &MainWindow::pushButtonTextChanged, this, &MainWindow::changeButtonText);

}

MainWindow::~MainWindow()
{
    delete ui;
}


/* 实现按钮点击槽函数 */
void MainWindow::pushButtonClicked()
{
    /* 使用emit发送信号 */
    emit pushButtonTextChanged();
}

/* 实现按钮文本改变的槽函数 */
void MainWindow::changeButtonText()
{
    /* 在槽函数里改变按钮的文本 */
    pushButton->setText("被点击了！");
}
