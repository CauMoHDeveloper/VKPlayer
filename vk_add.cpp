//Класс служит для джобавления в свои аудиозаписи композиции или для ее удаления из своего списка
//Принимает на вход id песни, id владельца песни, token
//Испускает сигнал в случае успеха

#include "vk_add.h"
using namespace QtJson;
vk_add::vk_add(QObject *parent) :
    QObject(parent)
{
    VkGet * get = new VkGet(this);

    connect(this, SIGNAL(get_process_song(QUrl)),get, SLOT(GET(QUrl)));
    connect(get, SIGNAL(data_get(QByteArray)), this, SLOT(response(QByteArray)));
}

void vk_add::add_song(QString audio_id,QString owner_id, QString token)                  //Добавить к себе аудиозапись
{
    QUrl current("https://api.vk.com/method/audio.add");
    QUrlQuery reqParams;
    reqParams.addQueryItem("owner_id", owner_id);
    reqParams.addQueryItem("audio_id", audio_id);
    reqParams.addQueryItem("access_token", token);
    current.setQuery(reqParams);

    emit get_process_song(current);
}

void vk_add::remove_song(QString audio_id, QString owner_id, QString token)              //Удалить аудиозапись
{
    QUrl current("https://api.vk.com/method/audio.delete");
    QUrlQuery reqParams;
    reqParams.addQueryItem("owner_id", owner_id);
    reqParams.addQueryItem("audio_id", audio_id);
    reqParams.addQueryItem("access_token", token);
    current.setQuery(reqParams);

    emit get_process_song(current);
}

void vk_add::response(QByteArray answer)                                                 //Посыл ответа на запрос удаления или добавления
{
    try
    {
        if(!answer.isNull() && !answer.isEmpty() && !answer.contains("error"))
        {
            QString List = parse(answer).toMap().value("response").toMap().value("aid").toString();
            emit complete();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Error add");
            msgBox.setWindowTitle("Ошибка");
            msgBox.exec();
        }
    }
    catch(QException)
    {

    }

    delete this;
}
