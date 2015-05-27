#ifndef VK_LYRICS_H
#define VK_LYRICS_H
#include "widget.h"
#include <QObject>

class vk_lyrics : public QObject
{
    Q_OBJECT
public:
    explicit vk_lyrics(QObject *parent = 0);

public slots:
    void get_lyrics(QString lyrics_id, QString token);
    void lyrics_parsing(QByteArray answer);

signals:
    void lyrics_get(QUrl);
    void send_lyrics(QString);

public slots:

};

#endif // VK_LYRICS_H
