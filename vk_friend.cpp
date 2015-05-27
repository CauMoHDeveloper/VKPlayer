//Класс служит для получения списка друзей
//При удачном скачивании списка формирует новый список и отправляет главному окну
//Работает Один раз за время жизни программы в отдельном потоке

#include "vk_friend.h"

using namespace QtJson;

VkFriend::VkFriend(QObject *parent) :
    QObject(parent)
{
    get = new VkGet(this);
}

void VkFriend::get_friends(QString Token)                         //Запрос на получения списа моих друзей
{
    QUrl current("https://api.vk.com/method/friends.get");
    QUrlQuery reqParams;
    reqParams.addQueryItem("access_token", Token);
    reqParams.addQueryItem("fields", "first_name");
    reqParams.addQueryItem("fields", "last_name");
    reqParams.addQueryItem("order", "hints");
    reqParams.addQueryItem("v", "3.0");
    current.setQuery(reqParams);

    QByteArray ans;
    ans = get->GET(current);

    this->parsing(ans);
}

void VkFriend::parsing(QByteArray answer)                                         //Парсинг мих друзей
{
    QString  tmpFULL;
    if(answer.isEmpty() || answer.contains("error"))
    {
        qDebug()<<"Empty List Friends";
        emit send_error("Empty List Friends. ");
        emit friends_parse(users);
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
            tmpFULL =   " " + current.value("first_name").toString() +
                        " " + current.value("last_name").toString();

            QPair<QString, QString> pair_users;
            pair_users.first = tmpFULL;
            pair_users.second = current.value("uid").toString();
            if(!pair_users.first.isEmpty())
                users.push_back(pair_users);
        }
        emit friends_parse(users);
        emit friends_loaded(true);
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error load friends list");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }

}


