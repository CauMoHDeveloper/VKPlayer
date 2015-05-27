#ifndef VK_ALBUMS_H
#define VK_ALBUMS_H
#include "widget.h"
#include <QObject>

class vk_albums : public QObject
{
    Q_OBJECT
public:
    explicit vk_albums(QObject *parent = 0);

public slots:
    void get_albums(QString UserId, QString token);
    void parsing(QByteArray answer);
signals:
    void albums_loaded(bool);
    void albums_get(QUrl);
    void albums_parse(QList< QPair<QString, QString> >);
    void send_error(QString);

private:
    QList< QPair<QString, QString> > albums;
    class VkGet * get;
};

#endif // VK_ALBUMS_H
