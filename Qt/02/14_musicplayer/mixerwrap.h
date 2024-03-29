#ifndef MIXERWRAP_H
#define MIXERWRAP_H

#include <QObject>

class MixerWrap : public QObject
{
    Q_OBJECT
public:
    explicit MixerWrap(QObject *parent = nullptr);

signals:

};

#endif // MIXERWRAP_H
