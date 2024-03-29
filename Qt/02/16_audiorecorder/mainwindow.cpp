#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 初始化布局 */
    layoutInit();

    /* 录制音频的类 */
    m_audioRecorder = new QAudioRecorder(this);

    /* 用于探测缓冲区的数据 */
    m_probe = new QAudioProbe(this);

    /* 设置探测的对象 */
    m_probe->setSource(m_audioRecorder);

    /* 播放器 */
    recorderPlayer = new QMediaPlayer(this);

    /* 播放列表 */
    mediaPlaylist = new QMediaPlaylist(this);

    recorderPlayer->setPlaylist(mediaPlaylist);

    /* 设置播放模式，默认是列表播放 */
    mediaPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);


    /* 扫描本地声卡设备 */
    devicesVar.append(QVariant(QString()));
    for (auto &device : m_audioRecorder->audioInputs())
    {
        devicesVar.append(QVariant(device));
        qDebug() << "本地声卡设备：" << device << " ";
    }
    /* 音频编码 */
    codecsVar.append(QVariant(QString()));
    for (auto &codecName : m_audioRecorder->supportedAudioCodecs())
    {
        codecsVar.append(QVariant(codecName));
        qDebug() << "音频编码：" << codecName <<  " ";
    }

    /* 容器/支持的格式 */
    containersVar.append(QVariant(QString()));
    for (auto &containerName : m_audioRecorder->supportedContainers())
    {
        containersVar.append(QVariant(containerName));
        qDebug() << "支持的格式：" << containerName <<  " ";
    }

    /* 采样率 */
    sampleRateVar.append(QVariant(0));
    for (int sampleRate : m_audioRecorder->supportedAudioSampleRates())
    {
        sampleRateVar.append(QVariant(sampleRate));
        qDebug() << "采样率：" << sampleRate << " ";
    }

    /* 通道 */
    channelsVar.append(QVariant(-1));
    channelsVar.append(QVariant(1));
    channelsVar.append(QVariant(2));
    channelsVar.append(QVariant(4));

    /* 质量 */
    qualityVar.append(QVariant(int(QMultimedia::LowQuality)));
    qualityVar.append(QVariant(int(QMultimedia::NormalQuality)));
    qualityVar.append(QVariant(int(QMultimedia::HighQuality)));

    /* 比特率 */
    bitratesVar.append(QVariant(0));
    bitratesVar.append(QVariant(32000));
    bitratesVar.append(QVariant(64000));
    bitratesVar.append(QVariant(96000));
    bitratesVar.append(QVariant(128000));

    /* 初始化时扫描已经录制的录音mp3文件 */
    scanRecordFiles();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::layoutInit()
{
    this->setMaximumSize(800, 480);
    this->setMinimumSize(800, 480);
    this->setWindowTitle("录音设备");

    mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    vBoxLayout = new QVBoxLayout();
    bottomWidget = new QWidget();
    listWidget = new QListWidget();
    listWidget->setFocusPolicy(Qt::NoFocus);
    listWidget->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);

    /* 垂直布局 */
    vBoxLayout->addWidget(listWidget);
    vBoxLayout->addWidget(bottomWidget);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    mainWidget->setLayout(vBoxLayout);

    bottomWidget->setMinimumHeight(80);
    bottomWidget->setMaximumHeight(80);
    bottomWidget->setStyleSheet("background:#cccccc");

    /* 水平布局 */
    hBoxLayout = new QHBoxLayout();

    /* 按钮，录音、上一首、下一首、删除项按钮 */
    recorderBt = new QPushButton();
    previousBt = new QPushButton();
    nextBt = new QPushButton();
    removeBt = new QPushButton();

    recorderBt->setCheckable(true);
    recorderBt->setObjectName("recorderBt");
    recorderBt->setFocusPolicy(Qt::NoFocus);
    recorderBt->setMaximumSize(60, 60);
    recorderBt->setMinimumSize(60, 60);

    hBoxLayout->setContentsMargins(0, 0, 0, 0);

    bottomWidget->setLayout(hBoxLayout);
    hBoxLayout->addWidget(recorderBt);
    hBoxLayout->addWidget(previousBt);
    hBoxLayout->addWidget(nextBt);
    hBoxLayout->addWidget(removeBt);

    nextBt->setMaximumSize(50, 50);
    removeBt->setMaximumSize(50, 50);
    previousBt->setMaximumSize(50, 50);

    previousBt->setObjectName("previousBt");
    removeBt->setObjectName("removeBt");
    nextBt->setObjectName("nextBt");

    previousBt->setFocusPolicy(Qt::NoFocus);
    removeBt->setFocusPolicy(Qt::NoFocus);
    nextBt->setFocusPolicy(Qt::NoFocus);

    /* 显示录音时长与录音Level */
    centerWidget = new QWidget(this);
    centerWidget->setGeometry(width() / 2 - 150,
                              height() / 2 - 100,
                              300,
                              200);
    centerWidget->setStyleSheet("QWidget { background:#8823242a;"
                                "border-radius:10px}");
    countLabel = new QLabel(centerWidget);
    countLabel->setGeometry(0,
                            0,
                            300,
                            50);
    countLabel->setStyleSheet("QLabel {font-size: 30px;color:#eeeeee;"
                              "font: blod;background:transparent}");
    countLabel->setAlignment(Qt::AlignCenter);
    levelHBoxLayout = new QHBoxLayout();

    for (int i = 0; i < 4; i++)
    {
        progressBar[i] = new QProgressBar();
        progressBar[i]->setOrientation(Qt::Vertical);
        progressBar[i]->setRange(0, 100);
        progressBar[i]->setVisible(false);
        progressBar[i]->setMaximumWidth(centralWidget()->width());
        levelHBoxLayout->addWidget(progressBar[i]);
        levelHBoxLayout->setContentsMargins(5, 50, 5, 5);
        progressBar[i]->setStyleSheet("QWidget { background:#22eeeeee;"
                                      "border-radius:0px}");
    }
    centerWidget->setLayout(levelHBoxLayout);
    centerWidget->hide();
    countLabel->raise();
}

void MainWindow::scanRecordFiles()
{
    mediaPlaylist->clear();
    listWidget->clear();
    mediaObjectInfo.clear();
    /* 录音文件保存在当前Sounds文件夹下 */
    QDir dir(QCoreApplication::applicationDirPath()
             + "/Sounds");
    QDir dirbsolutePath(dir.absolutePath());

    /* 如果文件夹不存在，则创建一个 */
    if(!dirbsolutePath.exists())
    {
        dirbsolutePath.mkdir(dirbsolutePath.absolutePath());
    }

    /* 定义过滤器 */
    QStringList filter;
    /* 包含所有xx后缀的文件 */
    filter << "*.mp3";
    /* 获取该目录下的所有文件 */
    QFileInfoList files =
        dirbsolutePath.entryInfoList(filter, QDir::Files);
    /* 遍历 */
    for (int i = 0; i < files.count(); i++)
    {
        MediaObjectInfo info;
        /* 使用utf-8编码 */
        info.fileName = QString::fromUtf8(files.at(i)
                                          .fileName()
                                          .toUtf8()
                                          .data());
        info.filePath = QString::fromUtf8(files.at(i)
                                          .filePath()
                                          .toUtf8()
                                          .data());
        /* 媒体列表添加音频 */
        if (mediaPlaylist->addMedia(
                    QUrl::fromLocalFile(info.filePath)))
        {
            /* 添加到容器数组里储存 */
            mediaObjectInfo.append(info);
            /* 添加音频名字至列表 */
            listWidget->addItem(
                new QListWidgetItem(QIcon(":/icons/play.png"),
                                    info.fileName));
        }
        else
        {
            qDebug() <<
                     mediaPlaylist->errorString()
                     .toUtf8().data()
                     << endl;
            qDebug() << "  Error number:"
                     << mediaPlaylist->error()
                     << endl;
        }
    }
}

