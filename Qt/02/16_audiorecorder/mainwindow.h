#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVariant>

#include <QList>

#include <QDir>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QAudioRecorder>
#include <QAudioProbe>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "mediaobjectinfo.h"
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

    /* 主Widget*/
    QWidget *mainWidget;

    /* 录音列表 */
    QListWidget *listWidget;

    /* 底部的Widget,用于存放按钮 */
    QWidget *bottomWidget;

    /* 中间的显示录制时长的Widget容器 */
    QWidget *centerWidget;

    /* 垂直布局 */
    QVBoxLayout *vBoxLayout;

    /* 录音Level布局 */
    QHBoxLayout *levelHBoxLayout;

    /* 水平布局 */
    QHBoxLayout *hBoxLayout;

    /* 录音按钮 */
    QPushButton *recorderBt;

    /* 上一首按钮 */
    QPushButton *previousBt;

    /* 下一首按钮 */
    QPushButton *nextBt;

    /* 删除按钮 */
    QPushButton *removeBt;

    /* 用于显示录音时长 */
    QLabel *countLabel;

    /* 用于显示录音level,最多四通道 */
    QProgressBar *progressBar[4];

    /* 录音类 */
    QAudioRecorder *m_audioRecorder = nullptr;

    /* 用于探测缓冲区的level */
    QAudioProbe *m_probe = nullptr;

    /* 媒体播放器，用于播放视频 */
    QMediaPlayer *recorderPlayer;

    /* 媒体列表 */
    QMediaPlaylist *mediaPlaylist;

    /* 录音媒体信息存储 */
    QVector<MediaObjectInfo> mediaObjectInfo;

    /* 录音设置容器，保存录音设备的可用信息，
     * 本例使用默认的信息，即可录音 */
    QList<QVariant>devicesVar;
    QList<QVariant>codecsVar;
    QList<QVariant>containersVar;
    QList<QVariant>sampleRateVar;

    QList<QVariant>channelsVar;
    QList<QVariant>qualityVar;
    QList<QVariant>bitratesVar;


    /* 布局初始化 */
    void layoutInit();

    /* 扫描录音文件 */
    void scanRecordFiles();

};
#endif // MAINWINDOW_H
