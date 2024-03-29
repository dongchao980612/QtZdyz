#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QMessageBox>
#include <QBoxLayout>

#include <QDir>
#include <QCoreApplication>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QVector>

#include <QMouseEvent>


#include "mediaobjectinfo.h" //媒体信息

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
    /* 布局初始化 */
    void musicLayout();

    /* 媒体播放器初始化 */
    void mediaPlayerInit();

    /* 扫描歌曲 */
    void scanSongs();

    /* 媒体播放器，用于播放音乐 */
    QMediaPlayer *musicPlayer;

    /* 媒体列表 */
    QMediaPlaylist *mediaPlaylist;

    /* 音乐列表 */
    QListWidget *listWidget;

    /* 音乐播放器按钮 */
    QPushButton *pushButton[7];

    /* 标签文本 */
    QLabel *label[4];

    /* 垂直布局 */
    QVBoxLayout *vBoxLayout[3];
    /* 水平布局 */
    QHBoxLayout *hBoxLayout[4];

    /* 垂直容器 */
    QWidget *vWidget[3];

    /* 水平容器 */
    QWidget *hWidget[4];

    /* 用于遮罩 */
    // QWidget *listMask;

    /* 播放进度条 */
    QSlider *durationSlider;

    /* 音乐进度条 */
    // QSlider *volumeSlider;


    /* 媒体信息存储 */
    QVector<MediaObjectInfo> mediaObjectInfo;

private slots:
    /* 播放按钮点击 */
    void btn_play_clicked();

    /* 下一曲按钮点击*/
    void btn_next_clicked();

    /* 上一曲按钮点击 */
    void btn_previous_clicked();

    /* 调整声音 */
    void btn_volume_clicked();



    /* 媒体状态改变 */
    void mediaPlayerStateChanged(QMediaPlayer::State);

    /* 媒体列表项改变 */
    void mediaPlaylistCurrentIndexChanged(int);

    /* 媒体总长度改变 */
    void musicPlayerDurationChanged(qint64);

    /* 媒体播放位置改变 */
    void mediaPlayerPositionChanged(qint64);



    /* 列表单击 */
    void listWidgetCliked(QListWidgetItem *);

    /* 播放进度条松开 */
    void durationSliderReleased();

    /* 声音进度条松开 */
    void volumeSliderReleased();



};
#endif // MAINWINDOW_H
