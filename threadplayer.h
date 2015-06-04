#ifndef THREADPLAYER_H
#define THREADPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QThread>

class ThreadPlayer : public QThread
{
    Q_OBJECT
public:
    ThreadPlayer();
    ~ThreadPlayer();

protected:
    void run();

private slots:
    void PlayerStarted();

signals:
    void sendPointPlayer(QMediaPlayer *obj);

public:
    QMediaPlayer *player;

};

#endif // THREADPLAYER_H
