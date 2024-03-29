#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>

#include <QTimer>
#include <QImage>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    ~Camera();

signals:
    /* 声明信号，用于传递有图片信号时显示图像 */
    void readyImage(const QImage &);

public slots:
    /* 定时器时间到处理函数，发送图像数据信号 */
    void timerTimeOut();

    /* 用于开启定时器 */
    void  selectCameraDevice(int index);

    /* 选择摄像头 */
    bool cameraProcess(bool bl);
private:
    /* 声明OpenCV的cv命名空间下的VideoCapture对象 */
    cv::VideoCapture *m_capture;

    /* 定时器 */
    QTimer *m_timer;

    /* 图像转换处理函数 */
    QImage matToQImage(const cv::Mat &);
};

#endif // CAMERA_H
