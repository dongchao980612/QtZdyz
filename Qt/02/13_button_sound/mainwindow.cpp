#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* 设置按钮文本 */
    ui-> pushButton->setGeometry(340, 220, 120, 40);
    ui-> pushButton->setText("按钮音效测试");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    /* 异步的方式播放 */
    QSound::play(":/audio/bell.wav");
}
