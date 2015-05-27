#ifndef VK_GET_H
#define VK_GET_H

#include <QtConcurrent/QtConcurrentRun>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>

class VkGet : public QObject
{
    Q_OBJECT
public:
    explicit VkGet(QObject *parent = 0);
    ~VkGet();

public slots:
    QByteArray GET(QUrl r);


signals:
    void data_get(QByteArray answer);
};

#endif // VK_GET_H
