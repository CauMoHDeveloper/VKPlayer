#include "audioedit.h"
#include "ui_audioedit.h"

//Класс Служит для редактирования аудиозаписей
//Включает в себя так же форму для редактирования
//На вход получает (Исполнителя, Название, Жанр, Id песни, Id Владельца, token
//При нажатии на кнопку сохранить отправляет запрос с новыми переменными
//При успешном ответе испускает сигнал который принимает главное окно для изменения Исполнителя,
//Название и Жанр в плейлисте


AudioEdit::AudioEdit(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::AudioEdit)
{
    ui->setupUi(this);

    this->setGeom("Audioedit");
    this->setWindowFlags( Qt::WindowStaysOnTopHint  );//Флаги окна виндоус
    this->DrawGUI();

    Genre.insert(1, "Rock");
    Genre.insert(2, "Pop");
    Genre.insert(3, "Rap & Hip-Hop");
    Genre.insert(4, "Easy Listening");
    Genre.insert(5, "Dance & House");
    Genre.insert(6, "Instrumental");
    Genre.insert(7, "Metal");
    Genre.insert(21, "Alternative");
    Genre.insert(8, "Dubstep");
    Genre.insert(9, "Jazz & Blues");
    Genre.insert(10, "Drum & Bass");
    Genre.insert(11, "Trance");
    Genre.insert(12, "Chanson");
    Genre.insert(13, "Ethnic");
    Genre.insert(14, "Acoustic & Vocal");
    Genre.insert(15, "Reggae");
    Genre.insert(16, "Classical");
    Genre.insert(17, "Indie Pop");
    Genre.insert(19, "Speech");
    Genre.insert(22, "Electropop & Disco");
    Genre.insert(18, "Other");

     this->setRoundedCorners(6,6,6,6);

    this->setWindowOpacity(0);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(0.95);
    animation->start();
}

AudioEdit::~AudioEdit()
{
    delete ui;
}



void AudioEdit::on_SaveEdit_clicked()
{
    flag = 1;
    QRect rect = ui->SaveEdit->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->SaveEdit, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+55, Y+12, 1, 1));
     animation->setEndValue(QRect(X, Y, 110, 24));
     animation->start();

    Artist_tmp = ui->ArtistEdit->text();
    Title_tmp = ui->TitleEdit->text();
    QString GenTmp;
    QString GenTmp_recieve;

    QMap<int,QString>::iterator it = Genre.begin();
    for(;it != Genre.end(); ++it)
    {
        if(it.value() == genre_tmp){
            GenTmp = QString("%1").arg(it.key());
            GenTmp_recieve = genre_tmp;
            break;
        }
        else{
            GenTmp = "18";
            GenTmp_recieve = "Other";
        }
    }

    VkGet *get = new VkGet(this);

    QUrl current("https://api.vk.com/method/audio.edit");
    QUrlQuery reqParams;

    reqParams.addQueryItem("owner_id", owner_id_tmp);
    reqParams.addQueryItem("audio_id", audio_id_tmp);
    reqParams.addQueryItem("artist", Artist_tmp);
    reqParams.addQueryItem("title", Title_tmp);
    reqParams.addQueryItem("genre_id", GenTmp);
    reqParams.addQueryItem("access_token", token_tmp);

    current.setQuery(reqParams);
    QString tmp = get->GET(current);

    Messages * messages = new Messages;
    QString title, text;

    if(tmp.indexOf("error",0) == -1){
        title = "Редактирование";
        text = "Удачно!";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        emit success_edit(Artist_tmp, Title_tmp, GenTmp_recieve);        
    }
    else{
        title = "Редактирование";
        text = "Ошибка!";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
    }
}

void AudioEdit::recieve_data(QString audio_id, QString owner_id, QString Artist, QString Title, QString genre, QString token)
{
    audio_id_tmp = audio_id;
    owner_id_tmp = owner_id;
    Artist_tmp = Artist;
    Title_tmp = Title;
    genre_tmp = genre;
    token_tmp = token;

    ui->ArtistEdit->setText(Artist_tmp);
    ui->TitleEdit->setText(Title_tmp);
    if(ui->GenreEdit->findText(genre_tmp) != -1){
        ui->GenreEdit->setCurrentText(genre_tmp);
    }
    else
        ui->GenreEdit->setCurrentText("Other");

    connect(ui->GenreEdit, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного жанра
            this, SLOT(GenreEdit(QString)));

    ui->ArtistEdit->setCursorPosition(0);
    ui->TitleEdit->setCursorPosition(0);
}

void AudioEdit::GenreEdit(QString val)
{
    genre_tmp = val;
}

void AudioEdit::DrawGUI()                                        //Рисование интерфейса
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    int r = settings->value("Color/R").toInt();
    int g = settings->value("Color/G").toInt();
    int b = settings->value("Color/B").toInt();
    QString styleSheet = "AudioEdit { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(r).arg(g).arg(b));

    ui->CloseApp->setStyleSheet("border-image: url(:/new/prefix1/icons/close.gif) stretch;");

    QString stylesheet_path;

    stylesheet_path = "://CSS/Label.txt";
    ui->ArtistLabel->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->TitleLabel->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->GenreLabel->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->ArtistEdit->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->TitleEdit->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/ComboBox.txt";
    ui->GenreEdit->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Button.txt";
    ui->SaveEdit->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    ui->Title->setStyleSheet(
                "color:white;"
                );

    ui->Icon->setStyleSheet("border-image: url(:/new/prefix1/vk.ico) stretch;");
}

void AudioEdit::on_CloseApp_clicked()
{
    this->saveGeom("Audioedit");
    this->close();
    if(flag != 1){
        deleteLater();
    }

}
