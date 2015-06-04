#include "threadplayer.h"
#include <QThread>

ThreadPlayer::ThreadPlayer()
{
    connect(this, SIGNAL(started()),
            this, SLOT(PlayerStarted()));
}

ThreadPlayer::~ThreadPlayer()
{

}

void ThreadPlayer::run()
{
    player = new QMediaPlayer();
    exec();
}

void ThreadPlayer::PlayerStarted()
{
    emit sendPointPlayer(player);
}
