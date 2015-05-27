#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <FMOD/inc/fmod.h>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);

signals:

public slots:
    void Play(QString url);
    void Pause(bool pause);
    void Stop();

private:
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound1;
    FMOD_CHANNEL     *channel;
    FMOD_RESULT       result;

};

#endif // ENGINE_H
