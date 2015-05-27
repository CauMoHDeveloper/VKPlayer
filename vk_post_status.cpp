//Класс для трансляции песни в статус пользователя
//На вход получает id песни, id пользователя и токен

#include "vk_post_status.h"

vk_post_status::vk_post_status(QObject *parent) :
    QObject(parent)
{
    VkGet * get = new VkGet;

    connect(this, SIGNAL(get_process_status(QUrl)),get, SLOT(GET(QUrl)));
    connect(get, SIGNAL(data_get(QByteArray)), this, SLOT(response(QByteArray)));

}


void vk_post_status::ins_status(QString audio_id, QString User_Id, QString token)     //Установить статус
{
    QUrl current("https://api.vk.com/method/audio.setBroadcast");
    QUrlQuery reqParams;
    if(audio_id.isNull())
    {
        reqParams.addQueryItem("audio", audio_id);
    }
    else
        reqParams.addQueryItem("audio", User_Id+"_"+audio_id);

    reqParams.addQueryItem("access_token", token);
    current.setQuery(reqParams);
    emit get_process_status(current);
}

void vk_post_status::response(QByteArray answer)                                 //Ответ удачно или нет поставлен статус
{
    QString tmp(answer), res;
    int LeftSkob = 0, RightSkob = 0;
    LeftSkob = tmp.indexOf("[", 0, Qt::CaseSensitive);
    RightSkob = tmp.indexOf("]", LeftSkob, Qt::CaseSensitive);
    res = tmp.mid(LeftSkob+1, RightSkob - LeftSkob-1);
    emit send_result();
}
