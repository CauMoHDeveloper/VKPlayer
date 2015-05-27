#include "engine.h"
#include <QDebug>

Engine::Engine(QObject *parent) :
    QObject(parent)
{

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, 0);
    FMOD_System_SetFileSystem(system, 0,0,0,0,0,0,-1);
    FMOD_System_SetStreamBufferSize(system,50000, FMOD_TIMEUNIT_RAWBYTES);
}

void Engine::Play(QString url)
{
    FMOD_Channel_Stop(channel);

    FMOD_CREATESOUNDEXINFO soundExInfo;
    memset(&soundExInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundExInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    soundExInfo.suggestedsoundtype = FMOD_SOUND_TYPE_MPEG;

    result = FMOD_System_CreateSound(system,url.toUtf8().data() , FMOD_HARDWARE |   FMOD_LOWMEM | FMOD_CREATESTREAM | FMOD_2D   ,&soundExInfo, &sound1);
    qDebug()<<result;

    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound1, 0, &channel);
    qDebug()<<result;

}

void Engine::Pause(bool pause)
{
    FMOD_Channel_SetPaused(channel, pause);
}

void Engine::Stop()
{
    FMOD_Channel_Stop(channel);
}
