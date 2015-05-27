#ifndef UPDATEVERSION_H
#define UPDATEVERSION_H
#include "widget.h"
#include <QObject>

class UpdateVersion : public QObject
{
    Q_OBJECT
public:
    explicit UpdateVersion(QObject *parent = 0);


public slots:
    void checkNew();
    void StartCheck();
    void StartUpdate();
    void replyFinished (QNetworkReply *reply);
    void downloader();


signals:
    void complete();
    void ErrorSignal(bool val);
    void Restarting();
    void NewVersionFound(bool val);

private:
    QNetworkAccessManager * manager;
    int flag;
    QString version;
    QString url;
};

#endif // UPDATEVERSION_H
