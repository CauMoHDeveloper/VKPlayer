#ifndef VK_POST_STATUS_H
#define VK_POST_STATUS_H

#include <QObject>
#include "widget.h"

class vk_post_status : public QObject
{
    Q_OBJECT
public:
    explicit vk_post_status(QObject *parent = 0);

signals:
    void get_process_status(QUrl);
    void send_result();

public slots:
    void ins_status(QString audio_id, QString User_Id, QString token);
    void response(QByteArray answer);

};

#endif // VK_POST_STATUS_H
