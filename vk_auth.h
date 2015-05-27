#ifndef VK_AUTH_H
#define VK_AUTH_H
#include "widget.h"

class VkAuth : public QObject
{
    Q_OBJECT
public:
    VkAuth();
    ~VkAuth();

public slots:
    void check_url(QUrl url);
    void readToken();
    void check_auth(QString UserId, QString token);
    void parsing_ckeck_auth(QByteArray answer);
    void get_My_photo(QString MyId);

signals:
    void auth_success(QString UserId,QString token);
    void ckeck_auth_current(QUrl);
    void check_auth_success(QString UserId, QString token);
    void auth_error(bool);
    void connect_error(bool);
    void send_My_photo(QString photo);

private:
    QString token, UserId;
    int attempt;


};

#endif // VK_AUTH_H
