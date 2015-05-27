#include "threadplayer.h"
#include <QThread>

ThreadPlayer::ThreadPlayer(QObject *parent) :
    QObject(parent)
{
}

void ThreadPlayer::runThread()
{
    QThread *thread = new QThread;
    player = new QMediaPlayer();
    player->setNotifyInterval(100);
    player->moveToThread(thread);
    thread->start();
    thread->setPriority(QThread::HighPriority);
}
