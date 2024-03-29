#ifndef MEDIAOBJECTINFO_H
#define MEDIAOBJECTINFO_H

#include <QString>

/* 媒体信息结构体 */
struct MediaObjectInfo
{
    /* 用于保存歌曲文件名 */
    QString fileName;

    /* 用于保存歌曲文件路径 */
    QString filePath;
};

#endif // MEDIAOBJECTINFO_H
