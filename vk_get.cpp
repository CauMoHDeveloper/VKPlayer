//Класс который отвечает за подключение к серверу вконтакте всех других классов
//Подается уже составленная ссылка от другого класса и отправляется северу
//На выходе массив байт в формате JSON

#include "vk_get.h"
#include <QMessageBox>

VkGet::VkGet(QObject *parent) :
    QObject(parent)
{
}


QByteArray VkGet::GET(QUrl r)   //Сетевое взаимодействие с сервером ВКонтакте
{

    try
    {
        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkReply* reply = manager->get(QNetworkRequest(r));
        QEventLoop wait;
        connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
        QTimer::singleShot(20000, &wait, SLOT(quit()));
        connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
        wait.exec();

        QByteArray answer = reply->readAll();
        reply->deleteLater();

        emit data_get(answer);
        return answer;
    }
    catch(QException)
    {
        return "";
    }
}

VkGet::~VkGet()
{
    qDebug()<<"Destr";
}
