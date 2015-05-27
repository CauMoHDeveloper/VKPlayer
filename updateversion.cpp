#include "updateversion.h"
#include <QSettings>
#include "messages.h"

//Класс имеет подключение к серверу обновления
//Может проверять наличие новой версии ( испускает сигнал есть или нет )
//Может скачивать новую версию( испускает сигнал о удачном скачивании)


UpdateVersion::UpdateVersion(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(this, SIGNAL(complete()), this, SLOT(checkNew()));

}

void UpdateVersion::checkNew()                                       //Проверить доступная новая версия или нет
{
    int OldValVersion = 0, NewValVersion = 0;

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    OldValVersion = settings->value("About/Version").toInt();
    NewValVersion = settings->value("UpdateVersion/Version").toInt();

    if(NewValVersion > OldValVersion)
    {
        emit NewVersionFound(true);
    }
    else
        emit NewVersionFound(false);
}

void UpdateVersion::StartCheck()                                     //Загрузка файла checkversion.txt
{
    flag = 1;
    url = "http://playervk.ru/checkversion.txt";
    this->downloader();
}

void UpdateVersion::StartUpdate()                                    //Старт скачки vkplayeract.exe
{
    Messages *messages = new Messages;
    messages->set_Title_and_Text("Обновление", "Идет обновление...", false, false);
    messages->show();

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    version = settings->value("UpdateVersion/Version").toString();
    url = settings->value("UpdateVersion/Url").toString();
    flag = 2;
    this->downloader();
}

void UpdateVersion::downloader()                                     //Метод для закачки файлов
{
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void UpdateVersion::replyFinished (QNetworkReply *reply)             //Запись во временный файл
{
        if(reply->error())
    {
        qDebug() << reply->errorString();
        emit ErrorSignal(false);
    }
    else
    {

       if(flag == 2)
       {
           QString tmpNameFile = "vkplayertemp.exe";

           QFile file(tmpNameFile);

             if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                 file.write("");
             file.close();

                 if(file.open(QFile::Append))
                 {
                     file.write(reply->readAll());
                     file.flush();
                     file.close();

                     QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

                     settings->setValue("About/Version", version);
                     settings->sync();
                     emit Restarting();
                 }
       }

       if(flag == 1)
       {
           QString str = reply->readAll();
           QStringList lst = str.split(" ");
           version = lst.at(0);
           url =  lst.at(1);

           QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

           settings->setValue("UpdateVersion/Version", version);
           settings->setValue("UpdateVersion/Url", url);
           settings->sync();
           emit complete();
       }
    }
 }
