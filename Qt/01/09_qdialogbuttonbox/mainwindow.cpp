#include "mainwindow.h"
/* 引入QDebug */
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* 主窗体设置位置和显示的大小 */
    this->setGeometry(0, 0, 800, 480);

    /* 实例化并设置按钮的盒子的大小和位置 */
    dialogButtonBox = new  QDialogButtonBox(this);
    dialogButtonBox->setGeometry(300, 200, 200, 30);

    /*使用Qt的Cancel按钮*/
    dialogButtonBox->addButton(QDialogButtonBox::Ok);
    dialogButtonBox->addButton(QDialogButtonBox::Cancel);


    /*将英文"Ok"按钮设置为中文"确认" */
    dialogButtonBox->button(QDialogButtonBox::Ok)->setText("确认");
    /*将英文"Cancel"按钮设置为中文"取消" */
    dialogButtonBox->button(QDialogButtonBox::Cancel)->setText("取消");


    /* 设定位置与大小 */
    pushButton = new QPushButton(tr("自定义"));

    /* 将pushButton添加到dialogButtonBox，并设定ButtonRole为ActionRole */
    dialogButtonBox->addButton(pushButton, QDialogButtonBox::ActionRole);

    /* 信号槽连接，带参数QAbstractButton *，用于判断用户点击哪个按键 */
    connect(dialogButtonBox, &QDialogButtonBox::clicked, this, &MainWindow::dialogButtonBoxClicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::dialogButtonBoxClicked(QAbstractButton *button)
{
    qDebug() << button->text();
    /* 判断点击的对象是否为QDialogButtonBox::Cancel */
    if(button == dialogButtonBox->button(QDialogButtonBox::Cancel))
    {
        /* 打印“单击了取消键” */
        qDebug() << "单击了取消键" << endl;
    }
    else if(button == dialogButtonBox->button(QDialogButtonBox::Ok))
    {
        /* 打印“单击了确认键” */
        qDebug() << "单击了确认键" << endl;
    }
    else if(button == pushButton)
    {
        /* 打印“单击了自定义键” */
        qDebug() << "单击了自定义键" << endl;
    }
}

