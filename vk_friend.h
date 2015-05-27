#ifndef VK_FRIEND_H
#define VK_FRIEND_H
#include "widget.h"
#include <QObject>

class VkFriend : public QObject
{
    Q_OBJECT
public:
    explicit VkFriend(QObject *parent = 0);

public slots:
    void get_friends(QString Token);
    void parsing(QByteArray answer);
signals:
    void friends_loaded(bool);
    void friend_get(QUrl);
    void friends_parse(QList< QPair<QString, QString> >);
    void send_error(QString);

private:
    QList< QPair<QString, QString> > users;
    class VkGet * get;

};

#endif // VK_FRIEND_H
