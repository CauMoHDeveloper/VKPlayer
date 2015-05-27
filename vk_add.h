#ifndef VK_ADD_H
#define VK_ADD_H
#include "widget.h"
#include <QObject>

class vk_add : public QObject
{
    Q_OBJECT
public:
    explicit vk_add(QObject *parent = 0);

public slots:
    void add_song(QString audio_id, QString owner_id, QString token);
    void remove_song(QString audio_id, QString owner_id, QString token);
    void response(QByteArray answer);

signals:
    void get_process_song(QUrl);
    void complete();

};

#endif // VK_ADD_H
