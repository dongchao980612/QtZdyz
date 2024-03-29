#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 视频播放器布局初始化 */
    videoLayout();

    /* 媒体初始化 */
    mediaPlayerInit();

    /* 扫描本地视频 */
    scanVideoFiles();

    /* 设置按钮的属性 */
    pushButton[0]->setCheckable(true);
    pushButton[4]->setCheckable(true);


    /* 按钮连接信号槽 */
    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(btn_play_clicked()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(btn_next_clicked()));
    connect(pushButton[2], SIGNAL(clicked()), this, SLOT(btn_volmedown_clicked()));
    connect(pushButton[3], SIGNAL(clicked()), this, SLOT(btn_volmeup_clicked()));
    connect(pushButton[4], SIGNAL(clicked()), this, SLOT(btn_fullscreen_clicked()));

    /* 列表连接信号槽 */
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listWidgetCliked(QListWidgetItem *)));

    /* 媒体连接信号槽 */
    connect(videoPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(mediaPlayerStateChanged(QMediaPlayer::State)));
    connect(videoPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(musicPlayerDurationChanged(qint64)));
    connect(videoPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(mediaPlayerPositionChanged(qint64)));
    connect(videoPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    // connect(videoPlayer, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error), this, SLOT(mediaPlayeError(QMediaPlayer::Error)));
    connect(videoPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(mediaPlayerError(QMediaPlayer::Error)));
    connect(mediaPlaylist, SIGNAL(currentIndexChanged(int)), this, SLOT(mediaPlaylistCurrentIndexChanged(int)));


    /* slider信号槽连接 */
    connect(durationSlider, SIGNAL(sliderReleased()), this, SLOT(durationSliderReleased()));
    connect(volumeSlider, SIGNAL(sliderReleased()), this, SLOT(volumeSliderReleased()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::videoLayout()
{
    this->setMinimumSize(800, 480);
    this->setMaximumSize(800, 480);
    this->setWindowTitle("视频播放器");

    for (int i = 0; i < 3; i++)
    {
        /* 水平容器 */
        hWidget[i] = new QWidget();
        hWidget[i]->setAutoFillBackground(true);
        /* 水平布局 */
        hBoxLayout[i] = new QHBoxLayout();
    }

    for (int i = 0; i < 2; i++)
    {
        /* 垂直容器 */
        vWidget[i] = new QWidget();
        vWidget[i]->setAutoFillBackground(true);
        /* 垂直布局 */
        vBoxLayout[i] = new QVBoxLayout();
    }

    for (int i = 0; i < 2; i++)
    {
        label[i] = new QLabel();
    }

    for (int i = 0; i < 5; i++)
    {
        pushButton[i] = new QPushButton();
        pushButton[i]->setMaximumSize(44, 44);
        pushButton[i]->setMinimumSize(44, 44);
    }

    /* 设置 */
    vWidget[0]->setObjectName("vWidget0");
    vWidget[1]->setObjectName("vWidget1");
    hWidget[1]->setObjectName("hWidget1");
    hWidget[2]->setObjectName("hWidget2");
    pushButton[0]->setObjectName("btn_play");
    pushButton[1]->setObjectName("btn_next");
    pushButton[2]->setObjectName("btn_volumedown");
    pushButton[3]->setObjectName("btn_volumeup");
    pushButton[4]->setObjectName("btn_screen");

    QFont font;

    font.setPixelSize(18);
    label[0]->setFont(font);
    label[1]->setFont(font);

    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::white);

    label[0]->setPalette(pal);
    label[1]->setPalette(pal);

    label[0]->setText("00:00");
    label[1]->setText("/00:00");

    durationSlider = new QSlider(Qt::Horizontal);
    durationSlider->setMaximumHeight(15);
    durationSlider->setObjectName("durationSlider");

    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setMaximumWidth(80);
    volumeSlider->setObjectName("volumeSlider");
    volumeSlider->setValue(50);

    listWidget = new QListWidget();
    listWidget->setObjectName("listWidget");
    listWidget->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);
    //listWidget->setFocusPolicy(Qt::NoFocus);
    videoWidget = new QVideoWidget();
    videoWidget->setStyleSheet("border-image: none;"
                               "background: transparent;"
                               "border:none");

    /* H0布局 */
    vWidget[0]->setMinimumSize(300, 480);
    vWidget[0]->setMaximumWidth(300);
    videoWidget->setMinimumSize(500, 480);

    hBoxLayout[0]->addWidget(videoWidget);
    hBoxLayout[0]->addWidget(vWidget[0]);

    hWidget[0]->setLayout(hBoxLayout[0]);
    hBoxLayout[0]->setContentsMargins(0, 0, 0, 0);

    setCentralWidget(hWidget[0]);

    /* V0布局 */
    QSpacerItem *vSpacer0 = new
    QSpacerItem(0, 80,
                QSizePolicy::Minimum,
                QSizePolicy::Maximum);
    vBoxLayout[0]->addWidget(listWidget);
    vBoxLayout[0]->addSpacerItem(vSpacer0);
    vBoxLayout[0]->setContentsMargins(0, 0, 0, 0);

    vWidget[0]->setLayout(vBoxLayout[0]);

    /* V1布局 */
    /* 底板部件布局 */
    hWidget[1]->setMaximumHeight(15);
    hWidget[2]->setMinimumHeight(65);
    vBoxLayout[1]->addWidget(hWidget[1]);
    vBoxLayout[1]->addWidget(hWidget[2]);
    vBoxLayout[1]->setAlignment(Qt::AlignCenter);

    vWidget[1]->setLayout(vBoxLayout[1]);
    vWidget[1]->setParent(this);
    vWidget[1]->setGeometry(0, this->height() - 80, this->width(), 80);
    vBoxLayout[1]->setContentsMargins(0, 0, 0, 0);
    /* 位于最上层 */
    vWidget[1]->raise();

    /* H1布局 */
    hBoxLayout[1]->addWidget(durationSlider);
    hBoxLayout[1]->setContentsMargins(0, 0, 0, 0);
    hWidget[1]->setLayout(hBoxLayout[1]);

    /* H2布局 */
    QSpacerItem *hSpacer0 = new
    QSpacerItem(300, 80,
                QSizePolicy::Expanding,
                QSizePolicy::Maximum);

    hBoxLayout[2]->addSpacing(20);
    hBoxLayout[2]->addWidget(pushButton[0]);
    hBoxLayout[2]->addSpacing(10);
    hBoxLayout[2]->addWidget(pushButton[1]);
    hBoxLayout[2]->addSpacing(10);
    hBoxLayout[2]->addWidget(pushButton[2]);
    hBoxLayout[2]->addWidget(volumeSlider);
    hBoxLayout[2]->addWidget(pushButton[3]);
    hBoxLayout[2]->addWidget(label[0]);
    hBoxLayout[2]->addWidget(label[1]);
    hBoxLayout[2]->addSpacerItem(hSpacer0);
    hBoxLayout[2]->addWidget(pushButton[4]);
    hBoxLayout[2]->addSpacing(20);
    hBoxLayout[2]->setContentsMargins(0, 0, 0, 0);
    hBoxLayout[2]->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    hWidget[2]->setLayout(hBoxLayout[2]);


#if 0
    hWidget[0]->setStyleSheet("background-color:red");
    hWidget[1]->setStyleSheet("background-color:blue");
    hWidget[2]->setStyleSheet("background-color:pink");
    vWidget[0]->setStyleSheet("background-color:yellow");
    vWidget[1]->setStyleSheet("background-color:green");
#endif
}

void MainWindow::scanVideoFiles()
{
    // QDir dir(QCoreApplication::applicationDirPath() + "/myVideo");
    QDir dir("G:\人民的名义");

    QDir dirbsolutePath(dir.absolutePath());
    /* 如果目录存在 */
    if (dirbsolutePath.exists())
    {
        /* 定义过滤器 */
        QStringList filter;
        /* 包含所有xx后缀的文件 */
        filter << "*.mp4" << "*.mkv" << "*.wmv" << "*.avi";

        /* 获取该目录下的所有文件 */
        QFileInfoList files = dirbsolutePath.entryInfoList(filter, QDir::Files);

        /* 遍历 */
        for (int i = 0; i < files.count(); i++)
        {
            MediaObjectInfo info;
            /* 使用utf-8编码 */
            info.fileName = QString::fromUtf8(files.at(i).fileName().toUtf8().data());
            info.filePath = QString::fromUtf8(files.at(i).filePath().toUtf8() .data());

            /* 媒体列表添加视频 */
            if (mediaPlaylist->addMedia(QUrl::fromLocalFile(info.filePath)))
            {
                /* 添加到容器数组里储存 */
                mediaObjectInfo.append(info);
                /* 添加视频名字至列表 */
                listWidget->addItem(info.fileName);
            }
            else
            {
                qDebug() << mediaPlaylist->errorString().toUtf8().data() << endl;
                qDebug() << "  Error number:" << mediaPlaylist->error() << endl;
            }
        }
    }
    else
    {
        QMessageBox::information(this, "提示", "文件夹不存在");
    }
}

void MainWindow::mediaPlayerInit()
{

    videoPlayer = new QMediaPlayer(this);
    mediaPlaylist = new QMediaPlaylist(this);

    /* 确保列表是空的 */
    mediaPlaylist->clear();

    /* 设置视频播放器的列表为mediaPlaylist */
    videoPlayer->setPlaylist(mediaPlaylist);

    /* 设置视频输出窗口 */
    videoPlayer->setVideoOutput(videoWidget);

    /* 设置播放模式，Loop是列循环 */
    mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);

    /* 设置默认软件音量为50% */
    videoPlayer->setVolume(50);
}

/* 播放按钮点击 */
void MainWindow::btn_play_clicked()
{
    int state = videoPlayer->state();
    switch (state)
    {
        case QMediaPlayer::StoppedState:
            /* 媒体播放 */
            videoPlayer->play();
            break;

        case QMediaPlayer::PlayingState:
            /* 媒体暂停 */
            videoPlayer->pause();
            break;

        case QMediaPlayer::PausedState:
            /* 设置视频输出窗口 */
            videoPlayer->play();
            break;
    }
}

/* 下一个视频按钮点击 */
void MainWindow::btn_next_clicked()
{
    videoPlayer->stop();
    int count = mediaPlaylist->mediaCount();
    if (0 == count)
    {
        return;
    }

    /* 列表下一个 */
    mediaPlaylist->next();
    videoPlayer->play();
}

/* 音量加 */
void MainWindow::btn_volmeup_clicked()
{
    /* 点击每次音量+5 */
    volumeSlider->setValue(volumeSlider->value() + 5);
    videoPlayer->setVolume(volumeSlider->value());
}

/* 音量减 */
void MainWindow::btn_volmedown_clicked()
{
    /* 点击每次音量-5 */
    volumeSlider->setValue(volumeSlider->value() - 5);
    videoPlayer->setVolume(volumeSlider->value());

}

/* 全屏 */
void MainWindow::btn_fullscreen_clicked()
{
    /* 全屏/非全屏操作 */
    vWidget[0]->setVisible(!pushButton[4]->isChecked());
}

/* 列表单击 */
void MainWindow::listWidgetCliked(QListWidgetItem *item)
{
    videoPlayer->stop();
    mediaPlaylist->setCurrentIndex(listWidget->row(item));
    videoPlayer->play();
}



/* 媒体状态改变 */
void MainWindow::mediaPlayerStateChanged(QMediaPlayer::State state)
{
    switch (state)
    {
        case QMediaPlayer::StoppedState:
            pushButton[0]->setChecked(false);
            break;

        case QMediaPlayer::PlayingState:
            pushButton[0]->setChecked(true);
            break;

        case QMediaPlayer::PausedState:
            pushButton[0]->setChecked(false);
            break;
    }
}

/* 媒体总长度改变 */
void MainWindow::musicPlayerDurationChanged(qint64 duration)
{
    durationSlider->setRange(0, duration / 1000);
    int second  = duration / 1000;
    int minute = second / 60;
    second %= 60;

    QString mediaDuration;
    mediaDuration.clear();

    if (minute >= 10)
    {
        mediaDuration = QString::number(minute, 10);
    }
    else
    {
        mediaDuration = "0" + QString::number(minute, 10);
    }

    if (second >= 10)
        mediaDuration = mediaDuration
                        + ":" + QString::number(second, 10);
    else
        mediaDuration = mediaDuration
                        + ":0" + QString::number(second, 10);

    /* 显示媒体总长度时间 */
    label[1]->setText("/" + mediaDuration);
}

/* 媒体播放位置改变 */
void MainWindow::mediaPlayerPositionChanged(qint64 position)
{
    if (!durationSlider->isSliderDown())
    {
        durationSlider->setValue(position / 1000);
    }

    int second  = position / 1000;
    int minute = second / 60;
    second %= 60;

    QString mediaPosition;
    mediaPosition.clear();

    if (minute >= 10)
    {
        mediaPosition = QString::number(minute, 10);
    }
    else
    {
        mediaPosition = "0" + QString::number(minute, 10);
    }

    if (second >= 10)
        mediaPosition = mediaPosition
                        + ":" + QString::number(second, 10);
    else
        mediaPosition = mediaPosition
                        + ":0" + QString::number(second, 10);

    /* 显示现在播放的时间 */
    label[0]->setText(mediaPosition);
}

/* 媒体列表项改变 */
void MainWindow::mediaPlaylistCurrentIndexChanged(int index)
{
    if (-1 == index)
    {
        return;
    }

    /* 设置列表正在播放的项 */
    listWidget->setCurrentRow(index);
}

/* 播放进度条松开 */
void MainWindow::durationSliderReleased()
{
    /* 设置媒体播放的位置 */
    videoPlayer->setPosition(durationSlider->value() * 1000);
}

/* 音量条松开 */
void MainWindow::volumeSliderReleased()
{
    /* 设置音量 */
    videoPlayer->setVolume(volumeSlider->value());
}

void MainWindow::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status)
    {
        case QMediaPlayer::UnknownMediaStatus:
            qDebug() << "媒体未知状况";
            break;
        case QMediaPlayer::NoMedia:
            qDebug() << "没有媒体文件！";
            break;
        case QMediaPlayer::BufferingMedia:
            qDebug() << "正在缓冲媒体文件！";
            break;
        case QMediaPlayer::BufferedMedia:
            qDebug() << "媒体文件缓冲完成！";
            break;
        case QMediaPlayer::LoadingMedia:
            qDebug() << "正在加载媒体！";
            break;
        case QMediaPlayer::StalledMedia:
            qDebug() << "播放停滞！";
            break;
        case QMediaPlayer::EndOfMedia:
            qDebug() << "播放结束！";
            break;
        case QMediaPlayer::LoadedMedia:
            qDebug() << "媒体加载完成！";
            break;
        case QMediaPlayer::InvalidMedia:
            qDebug() << "不可用的媒体文件！";
            break;
        default:
            break;
    }

}

void MainWindow::mediaPlayerError(QMediaPlayer::Error error)
{
    switch (error)
    {
        case QMediaPlayer::NoError:
            qDebug() << "没有错误！";
            break;
        case QMediaPlayer::ResourceError:
            qDebug() << "媒体资源无法被解析！";
            break;
        case QMediaPlayer::FormatError:
            qDebug() << "不支持该媒体格式！";
            break;
        case QMediaPlayer::NetworkError:
            qDebug() << "发生了一个网络错误！";
            break;
        case QMediaPlayer::AccessDeniedError:
            qDebug() << "没有播放权限！";
            break;
        case QMediaPlayer::ServiceMissingError:
            qDebug() << "没有发现有效的播放服务！";
            break;
        default:
            break;
    }

}

