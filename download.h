#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "widget.h"
#include <QProgressDialog>

class Download : public QObject
{
    Q_OBJECT
public:
    Download();
    ~Download();
signals:
    void recieve();
    void complete();
    void complete_ad();

public slots:
    void reciveDoc(QUrl tmpU, QString tmpF, QString File_Name);            //Прием Url песни и директории для загрузки
    void downloader();                                  //основная функция загрузки
    void dataReadProgress(qint64 done, qint64 total);   //Вывод загрузки в прогресс диалог
    void replyFinished (QNetworkReply *reply);          //запись в файл
    void abort_downloading();
    void error_Reply(QNetworkReply::NetworkError);
    void error_Ssl(QList<QSslError>);

private:
    QUrl url;                         //Url песни
    QString filePath;                 //Путь для загрузки
    QString _File_Name;                //Имя Файла
    QProgressDialog * progress;       //объект класса прогресс
    QNetworkAccessManager * manager;
};

#endif // DOWNLOAD_H
