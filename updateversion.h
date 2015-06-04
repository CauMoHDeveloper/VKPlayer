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
    void dataReadProgress(qint64 done, qint64 total);   //Вывод загрузки в прогресс диалог
    void downloader();
    void error_Reply(QNetworkReply::NetworkError);
    void error_Ssl(QList<QSslError>);


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
    QProgressDialog * progress;       //объект класса прогресс
    class Messages *messagesStartUpdate;
    bool Stop_update;
};

#endif // UPDATEVERSION_H
