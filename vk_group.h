#ifndef VK_GROUP_H
#define VK_GROUP_H
#include "widget.h"
#include <QObject>

class vk_group : public QObject
{
    Q_OBJECT
public:
    explicit vk_group(QObject *parent = 0);

public slots:
    void get_groups(QString UserId, QString token);
    void parsing(QByteArray answer);
signals:
    void groups_loaded(bool);
    void group_get(QUrl);
    void groups_parse(QList< QPair<QString, QString> >);
    void send_error(QString);

private:
    QList< QPair<QString, QString> > groups;
    class VkGet * get;

};

#endif // VK_GROUP_H
