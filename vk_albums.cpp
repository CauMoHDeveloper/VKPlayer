#include "vk_albums.h"

//Класс служит для получения списка групп
//При удачном скачивании списка формирует новый список и отправляет главному окну
//Работает Один раз за время жизни программы в отдельном потоке


using namespace QtJson;

vk_albums::vk_albums(QObject *parent) :
    QObject(parent)
{
    get = new VkGet(this);
}

void vk_albums::get_albums(QString UserId, QString token)                         //Запрос на получения списа моих альбомов
{

    QUrl current("https://api.vk.com/method/audio.getAlbums");
    QUrlQuery reqParams;
    reqParams.addQueryItem("access_token", token);
    reqParams.addQueryItem("owner_id", UserId);
    reqParams.addQueryItem("count", "50");

    current.setQuery(reqParams);

    QByteArray ans;
    ans = get->GET(current);

    this->parsing(ans);
}

void vk_albums::parsing(QByteArray answer)                                         //Парсинг мих альбомов
{
    QString  title;
    if(answer.isEmpty() || answer.contains("error"))
    {
        qDebug()<<"Empty albums list";
        emit albums_parse(albums);
        return;
    }
    long int first = answer.indexOf("[");
    long int size = answer.size();
    for(int i = first + 1; i < size; i++){
        if(answer[i] == '['){
            answer.replace(i, answer.indexOf("]") - i + 1, "1");
        }
            size = answer.size();
    }
    try
    {
        QVariantList List = parse(answer).toMap().value("response").toList();

        for(int i=0; i < List.size(); i++)
        {
            QVariantMap current = List[i].toMap();
            title =   " " + current.value("title").toString();
            QPair<QString, QString> pair_albums;
            pair_albums.first = title;
            pair_albums.second = current.value("album_id").toString();
            if(!pair_albums.second.isEmpty())
                albums.push_back(pair_albums);
        }

        emit albums_parse(albums);
        emit albums_loaded(true);
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error load albums list");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }

}

