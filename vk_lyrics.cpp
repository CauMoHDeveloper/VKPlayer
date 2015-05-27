//Данный класс скачивает и формирует текст песни
//На вход получает id текста песни и токен
//На выходе сформированный текст песни

#include "vk_lyrics.h"

using namespace QtJson;
vk_lyrics::vk_lyrics(QObject *parent) :
    QObject(parent)
{
    VkGet * get = new VkGet(this);

    connect(this, SIGNAL(lyrics_get(QUrl)),get, SLOT(GET(QUrl)));
    connect(get, SIGNAL(data_get(QByteArray)), this, SLOT(lyrics_parsing(QByteArray)));
}

void vk_lyrics::get_lyrics(QString lyrics_id, QString token)                     //Получения текста песни
{
    QUrl current("https://api.vk.com/method/audio.getLyrics");
    QUrlQuery reqParams;
    reqParams.addQueryItem("lyrics_id", lyrics_id);
    reqParams.addQueryItem("access_token", token);
    current.setQuery(reqParams);

    emit lyrics_get(current);
}

void vk_lyrics::lyrics_parsing(QByteArray answer)                                //Парсинг текста песни
{
    try
    {
        if(!answer.isEmpty() || !answer.contains("error"))
        {
            QString List = parse(answer).toMap().value("response").toMap().value("text").toString();
            emit send_lyrics(List);
        }
        else
            emit send_lyrics("Ошибка");
    }
    catch(QException)
    {
        emit send_lyrics("Ошибка");
    }
}
