#include "vk_audiopop.h"

//Класс который скачивает список аудиозаписей
//В зависимости от того, к какому методу вконтакте обращаться, формирует разные запросы
//Формирует список аудиозаписей и отправляет его главному окну

using namespace QtJson;

VkAudiopop::VkAudiopop()
{
    VkGet * get = new VkGet(this);

    connect(this, SIGNAL(audiopop_get(QUrl)),get, SLOT(GET(QUrl)));
    connect(get, SIGNAL(data_get(QByteArray)), this, SLOT(audiopop_parsing(QByteArray)));
}

VkAudiopop::~VkAudiopop()
{
    delete this;
}

void VkAudiopop::get_audioPOPULAR(QString UserId, QString token,QUrl current,QString search,int MyFlag, int Friend_or_Group, int offset) //Запрос на получение списка песен
{
    flag = 0;
    QUrl tmp("https://api.vk.com/method/audio.get");
    QUrl tmp2("https://api.vk.com/method/audio.search");
    QUrl tmp3("https://api.vk.com/method/audio.getPopular");
    QUrlQuery reqParams;
    reqParams.addQueryItem("count", "150");
    reqParams.addQueryItem("access_token", token);
    reqParams.addQueryItem("offset", QString("%1").arg(offset));
    reqParams.addQueryItem("v", "3.0");
    if(current==tmp)
    {
        Fr_Gr = Friend_or_Group;
        if(Friend_or_Group == 2){
            reqParams.addQueryItem("owner_id", "-"+UserId);
            group_id = UserId;
        }
        else if(Friend_or_Group == 3)
        {
            reqParams.addQueryItem("owner_id", UserId);
            reqParams.addQueryItem("album_id", search);
        }
        else
        {
             reqParams.addQueryItem("owner_id", UserId);
             if(MyFlag == 1)
             {
                 reqParams.addQueryItem("need_user", "1");
                 flag = 1;
             }
        }
    }
    if(current==tmp2)
    {
        reqParams.addQueryItem("q", search);
        reqParams.addQueryItem("auto_complete", "1");
        reqParams.addQueryItem("sort", "2");
    }
    if(current==tmp3 && search!="empty"){
        reqParams.addQueryItem("genre_id", search);
    }

    current.setQuery(reqParams);

    qDebug()<<current;

    emit audiopop_get(current);

}

void VkAudiopop::audiopop_parsing(QByteArray answer)      //Парсинг списка песен
{
    int FL = 1;
    if(answer.isEmpty() || answer.contains("error_code"))
    {
        qDebug()<<"Access to users audio is denied";
        if(flag == 1)
        {
            emit send_photo(photo_user);
            photo_user.first.clear();
            photo_user.second.clear();
            flag = 0;
        }
        if(Fr_Gr == 2){
            emit send_group_id(group_id);
            group_id.clear();
            flag = 0;
            Fr_Gr = 0;
        }
        emit audio_table(Artist_Title, Id_Url, Duration_Genre, OwnerId_lyricsId);

        QMessageBox msgBox;
        msgBox.setText("Error Load playlist");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();


        return;
    }

    try
    {
        QVariantList List = parse(answer).toMap().value("response").toList();

        for(int i = 0; i < List.size(); i++)
            {
                QVariantMap current = List[i].toMap();


                QPair<QString, QString> pair_Id_Url;
                pair_Id_Url.first = current.value("aid").toString();
                pair_Id_Url.second = current.value("url").toString();
                if(!pair_Id_Url.first.isEmpty())
                    Id_Url.push_back(pair_Id_Url);


                QPair<QString, QString> pair_Artist_Title;
                pair_Artist_Title.first = current.value("artist").toString();
                pair_Artist_Title.second = current.value("title").toString();
                if(!pair_Id_Url.first.isEmpty())
                    Artist_Title.push_back(pair_Artist_Title);

                QPair<QString, QString> pair_OwnerId_lyricsId;
                pair_OwnerId_lyricsId.first = current.value("owner_id").toString();
                pair_OwnerId_lyricsId.second = current.value("lyrics_id").toString();
                if(!pair_Id_Url.first.isEmpty())
                    OwnerId_lyricsId.push_back(pair_OwnerId_lyricsId);

                QString tmpD = current.value("duration").toString();
                QString Duration;
                qint64 a , min, sec;
                a = tmpD.toInt();
                min=a/60;
                sec=a%60;
                if(sec < 10)
                {
                     Duration = QString("%1:0%2").arg(min).arg(sec);
                }
                else
                {
                     Duration = QString("%1:%2").arg(min).arg(sec);
                }

                QPair<QString, QString> pair_Duration_Genre;
                pair_Duration_Genre.first = Duration;
                QString tempGenre = current.value("genre").toString();
                int tmp = tempGenre.toInt();

                switch(tmp)
                {
                    case 1 : pair_Duration_Genre.second = "Rock"; break;
                    case 2 : pair_Duration_Genre.second = "Pop"; break;
                    case 3 : pair_Duration_Genre.second = "Rap & Hip-Hop"; break;
                    case 4 : pair_Duration_Genre.second = "Easy Listening"; break;
                    case 5 : pair_Duration_Genre.second = "Dance & House"; break;
                    case 6 : pair_Duration_Genre.second = "Instrumental"; break;
                    case 7 : pair_Duration_Genre.second = "Metal"; break;
                    case 21 : pair_Duration_Genre.second = "Alternative"; break;
                    case 8 : pair_Duration_Genre.second = "Dubstep"; break;
                    case 9 : pair_Duration_Genre.second = "Jazz & Blues"; break;
                    case 10 : pair_Duration_Genre.second = "Drum & Bass"; break;
                    case 11 : pair_Duration_Genre.second = "Trance"; break;
                    case 12 : pair_Duration_Genre.second = "Chanson"; break;
                    case 13 : pair_Duration_Genre.second = "Ethnic"; break;
                    case 14 : pair_Duration_Genre.second = "Acoustic & Vocal"; break;
                    case 15 : pair_Duration_Genre.second = "Reggae"; break;
                    case 16 : pair_Duration_Genre.second = "Classical"; break;
                    case 17 : pair_Duration_Genre.second = "Indie Pop"; break;
                    case 19 : pair_Duration_Genre.second = "Speech"; break;
                    case 22 : pair_Duration_Genre.second = "Electropop & Disco"; break;
                    case 18 : pair_Duration_Genre.second = "Other"; break;
                }
                if(!pair_Id_Url.first.isEmpty())
                    Duration_Genre.push_back(pair_Duration_Genre);

                if(flag == 1 && FL == 1 && photo_user.first.isEmpty())
                {
                    QString photo = current.value("photo").toString();
                    QString name = current.value("name").toString();
                    photo_user.first = name;
                    photo_user.second = photo;
                }

            }

        if(flag == 1)
        {
            emit send_photo(photo_user);
            photo_user.first.clear();
            photo_user.second.clear();
            flag = 0;
        }
        if(Fr_Gr == 2){
            emit send_group_id(group_id);
            group_id.clear();
            flag = 0;
            Fr_Gr = 0;
        }
        if(Fr_Gr == 3)
        {
            emit signal_create_newTab();
            flag = 0;
            Fr_Gr = 0;
        }

        emit audio_table(Artist_Title, Id_Url, Duration_Genre, OwnerId_lyricsId);

        Artist_Title.clear();
        Id_Url.clear();
        Duration_Genre.clear();
        OwnerId_lyricsId.clear();
        List.clear();
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error Load playlist");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }



}
