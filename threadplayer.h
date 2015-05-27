#ifndef THREADPLAYER_H
#define THREADPLAYER_H

#include <QObject>
#include <QMediaPlayer>

class ThreadPlayer : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPlayer(QObject *parent = 0);
    QMediaPlayer *player;

signals:

public slots:
    void runThread();
};

#endif // THREADPLAYER_H
