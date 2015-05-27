#ifndef VK_SEND_ATTACHMENT_H
#define VK_SEND_ATTACHMENT_H

#include <QObject>
#include "widget.h"

class vk_send_attachment : public QObject
{
    Q_OBJECT
public:
    explicit vk_send_attachment(QObject *parent = 0);

signals:
    void get_process_attachment(QUrl);
    void send_result(QString);


public slots:
    void process_attachment(QString audio_id, QString owner_id, QString UsId, QString token, int type);
    void response(QByteArray answer);

};

#endif // VK_SEND_ATTACHMENT_H
