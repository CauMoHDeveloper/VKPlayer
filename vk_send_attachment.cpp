//Данный класс служит для отправки песни сообщением друзьям,
//Отправки песни на стену друзьям, самому себе, группам.
//на вход принимает id песни, id владельца, id пользователя, token и флаг (в зависимости какой именно метод вконтакте использвоать)


#include "vk_send_attachment.h"

vk_send_attachment::vk_send_attachment(QObject *parent) :
    QObject(parent)
{
    VkGet * get = new VkGet;

    connect(this, SIGNAL(get_process_attachment(QUrl)),get, SLOT(GET(QUrl)));
    connect(get, SIGNAL(data_get(QByteArray)), this, SLOT(response(QByteArray)));
}

void vk_send_attachment::process_attachment(QString audio_id, QString owner_id, QString UsId,  QString token, int type)     //Прикрепить вложение
{
    QUrl current;
    if(type == 0 || type == 3)
        current = "https://api.vk.com/method/wall.post";
    else
        current = "https://api.vk.com/method/messages.send";

    QUrlQuery reqParams;

    if(type == 0 || type == 3)
    {
        if(type == 0)
            reqParams.addQueryItem("owner_id", UsId);
        else
            reqParams.addQueryItem("owner_id", "-"+UsId);

        qDebug()<<UsId;
        reqParams.addQueryItem("message", "( Отправлено из VKPlayer ) http://playervk.ru");
        reqParams.addQueryItem("attachments", "audio"+owner_id+"_"+audio_id);
        reqParams.addQueryItem("access_token", token);
    }
    else
    {
        reqParams.addQueryItem("user_id", UsId);
        reqParams.addQueryItem("message", "( Отправлено из VKPlayer ) http://playervk.ru");
        reqParams.addQueryItem("attachment", "audio"+owner_id+"_"+audio_id);
        reqParams.addQueryItem("access_token", token);
    }


    current.setQuery(reqParams);
    emit get_process_attachment(current);
}

void vk_send_attachment::response(QByteArray answer)                                 //Ответ удачно или нет поставлен статус
{
    QString tmp(answer), res;
    int LeftSkob = 0, RightSkob = 0;
    LeftSkob = tmp.indexOf("[", 0, Qt::CaseSensitive);
    RightSkob = tmp.indexOf("]", LeftSkob, Qt::CaseSensitive);
    res = tmp.mid(LeftSkob+1, RightSkob - LeftSkob-1);
    emit send_result(res);
    delete this;
}
