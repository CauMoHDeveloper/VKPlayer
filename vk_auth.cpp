
//Класс служит для авторизации пользователя
//Проверяет сохраненный токен и айди, если они валидные то испускает сигнал success
//Если нет то испускает сигнал (ввести логин пас )
//Если не получает ответа ответа от сервера вконтакте то испускает сигнал (нет интернета)
//Сохраняет новый токен и айди в файл data.txt

#include "vk_auth.h"
#include <QObject>
#include <QSettings>

using namespace QtJson;


VkAuth::VkAuth()
{
    VkGet * get = new VkGet;
    connect(this,SIGNAL(check_auth_success(QString, QString)), this, SLOT(check_auth(QString, QString)));
    connect(this, SIGNAL(ckeck_auth_current(QUrl)),get, SLOT(GET(QUrl)));
    connect(get, SIGNAL(data_get(QByteArray)), this, SLOT(parsing_ckeck_auth(QByteArray)));

    attempt = 0;
}

VkAuth::~VkAuth()
{

}

void VkAuth::check_url(QUrl url)                                           //Запрос на получение токена и айди
{
    if(!url.toString().contains("access_token"))
        return;

    url = url.toString().replace("#", "?");

    token = QUrlQuery(url).queryItemValue("access_token");
    UserId = QUrlQuery(url).queryItemValue("user_id");

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    settings->setValue("TokenAndId/Token", token);
    settings->setValue("TokenAndId/Id", UserId);
    settings->sync();

    emit auth_success(token, UserId);
}

void VkAuth::readToken()                                                   //Прочесть файл для загрузки токена и айди
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    token = settings->value("TokenAndId/Token").toString();
    UserId = settings->value("TokenAndId/Id").toString();

    qDebug() << token << UserId;
    emit check_auth_success(UserId, token);
}

void VkAuth::check_auth(QString UserId, QString token)                     //Проверка валидности токена и айди
{
    QUrl current("https://api.vk.com/method/audio.get");

    QUrlQuery reqParams;
    reqParams.addQueryItem("count", "1");
    reqParams.addQueryItem("owner_id", UserId);
    reqParams.addQueryItem("access_token", token);

    current.setQuery(reqParams);

    emit ckeck_auth_current(current);
}

void VkAuth::parsing_ckeck_auth(QByteArray answer)                         //парсинг токена и айди
{
     if(answer.contains("response"))
     {
         emit auth_success(token, UserId);
     }
     if(answer.isEmpty()){
         if(attempt <= 2)
         {
             this->readToken();
             attempt++;
         }
         else
            emit connect_error(true);                       //Нет интернета
     }
     if(answer.contains("error"))
     {
         emit auth_error(false);                         //Ошибка авторизации
     }
}

QString VkAuth::get_My_photo(QString MyId)                                    //Получение моей аватарки
{
    VkGet * get = new VkGet(this);
    QUrl current("https://api.vk.com/method/users.get");
    QUrlQuery reqParams;
    reqParams.addQueryItem("user_ids", MyId);
    reqParams.addQueryItem("fields", "photo_100");
    current.setQuery(reqParams);
    QByteArray answer = get->GET(current);
    try
    {
        if(!answer.isEmpty() || !answer.contains("error"))
        {
            QVariantList List = parse(answer).toMap().value("response").toList();
            QVariantMap tmp = List[0].toMap();
            QString photo = tmp.value("photo_100").toString();
            return photo;
            //emit send_My_photo(photo);
        }
        else
            return " ";
    }
    catch(QException)
    {
        //emit send_My_photo("");
        return " ";
    }

}

