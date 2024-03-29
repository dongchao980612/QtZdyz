#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QMessageBox>

#include <QListWidget>
#include <QVideoWidget>

#include <QDir>

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

    /* 媒体播放器，用于播放视频 */
    QMediaPlayer *videoPlayer;

    /* 媒体列表 */
    QMediaPlaylist *mediaPlaylist;

    /* 媒体信息存储 */
    QVector<MediaObjectInfo> mediaObjectInfo;


    /* 水平容器 */
    QWidget *hWidget[3];

    /* 垂直容器 */
    QWidget *vWidget[2];

    /* 垂直布局 */
    QVBoxLayout *vBoxLayout[2];

    /* 水平布局 */
    QHBoxLayout *hBoxLayout[3];

    /* 标签文本 */
    QLabel *label[2];

    /* 视频播放器按钮 */
    QPushButton *pushButton[5];

    /* 播放进度条 */
    QSlider *durationSlider;

    /* 音量条 */
    QSlider *volumeSlider;


    /* 视频列表 */
    QListWidget *listWidget;

    /* 视频显示窗口 */
    QVideoWidget *videoWidget;

    /* 视频布局函数 */
    void videoLayout();

    /* 扫描本地视频文件 */
    void scanVideoFiles();

    /* 媒体初始化 */
    void mediaPlayerInit();

private slots:
    /* 播放按钮点击 */
    void btn_play_clicked();

    /* 下一个视频按钮点击 */
    void btn_next_clicked();

    /* 音量加 */
    void btn_volmeup_clicked();

    /* 音量减 */
    void btn_volmedown_clicked();

    /* 全屏 */
    void btn_fullscreen_clicked();


    /* 列表单击 */
    void listWidgetCliked(QListWidgetItem *);


    /* 媒体状态改变 */
    void mediaPlayerStateChanged(QMediaPlayer::State);

    /* 媒体总长度改变 */
    void musicPlayerDurationChanged(qint64);

    /* 媒体播放位置改变 */
    void mediaPlayerPositionChanged(qint64);

    /* 媒体列表项改变 */
    void mediaPlaylistCurrentIndexChanged(int);

    /* 播放进度条松开 */
    void durationSliderReleased();

    /* 音量条松开 */
    void volumeSliderReleased();

    // **************************
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void mediaPlayerError(QMediaPlayer::Error);
    // **************************


};
#endif // MAINWINDOW_H
