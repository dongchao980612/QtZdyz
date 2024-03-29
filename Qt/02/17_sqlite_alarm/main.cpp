#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "switchbutton.h"
#include "numberpicker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    /* 指定文件 */
    QFile file(":/style.qss");

    /* 判断文件是否存在 */
    if (file.exists() )
    {
        /* 以只读的方式打开 */
        file.open(QFile::ReadOnly);
        /* 以字符串的方式保存读出的结果 */
        QString styleSheet = QLatin1String(file.readAll());
        /* 设置全局样式 */
        qApp->setStyleSheet(styleSheet);
        /* 关闭文件 */
        file.close();
    }
#endif
    MainWindow w;
    w.show();
    return a.exec();
}
