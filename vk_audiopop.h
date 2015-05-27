#ifndef VK_AUDIOPOP_H
#define VK_AUDIOPOP_H
#include "widget.h"

class VkAudiopop : public QObject
{
    Q_OBJECT
public:
    VkAudiopop();
    ~VkAudiopop();

public slots:
    void get_audioPOPULAR(QString UserId, QString token, QUrl current, QString search, int MyFlag, int Friend_or_Group, int offset);
    void audiopop_parsing(QByteArray answer);

signals:
    void audiopop_get(QUrl);
    void audio_table( QList< QPair<QString, QString> >,QList< QPair<QString, QString> >,QList< QPair<QString, QString> >, QList< QPair<QString, QString> >);
    void send_photo(QPair<QString, QString> );
    void send_group_id(QString);
    void signal_create_newTab();

private:
    QList< QPair<QString, QString> > Id_Url;               //Включает в себя Id песни и URL песни
    QList< QPair<QString, QString> > Artist_Title;         //Включает в себя артиста и название
    QList< QPair<QString, QString> > Duration_Genre;       //Включает в себя Длину песни и Жанр
    QList< QPair<QString, QString> > OwnerId_lyricsId;     //Включает в себя идентификатор владельца аудиозаписей и Текст песни
    QPair<QString, QString> photo_user;                    //Включает в себя Имя Фамилию пользователя и Его Аватарку
    int flag;
    int Fr_Gr;
    QString group_id;
};

#endif // VK_AUDIOPOP_H
