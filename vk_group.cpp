//Класс служит для получения списка групп
//При удачном скачивании списка формирует новый список и отправляет главному окну
//Работает Один раз за время жизни программы в отдельном потоке

#include "vk_group.h"

using namespace QtJson;

vk_group::vk_group(QObject *parent) :
    QObject(parent)
{
    get = new VkGet(this);
}

void vk_group::get_groups(QString UserId, QString token)                         //Запрос на получения списа моих групп
{

    QUrl current("https://api.vk.com/method/groups.get");
    QUrlQuery reqParams;
    reqParams.addQueryItem("access_token", token);
    reqParams.addQueryItem("user_id", UserId);
    reqParams.addQueryItem("extended", "1");
    reqParams.addQueryItem("count", "1000");

    current.setQuery(reqParams);

    QByteArray ans;
    ans = get->GET(current);

    this->parsing(ans);


}

void vk_group::parsing(QByteArray answer)                                         //Парсинг мих групп
{
    QString  tmpFULL;
    if(answer.isEmpty() || answer.contains("error"))
    {
        qDebug()<<"Empty List Groups";
        emit send_error("Empty List Groups. ");
        emit groups_parse(groups);
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
            tmpFULL =   " " + current.value("name").toString();

            QPair<QString, QString> pair_groups;
            pair_groups.first = tmpFULL;
            pair_groups.second = current.value("gid").toString();
            if(!pair_groups.second.isEmpty())
                groups.push_back(pair_groups);
        }
        emit groups_parse(groups);
        emit groups_loaded(true);
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error load groups list");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }

}
