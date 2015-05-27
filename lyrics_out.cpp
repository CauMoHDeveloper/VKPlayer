#include "lyrics_out.h"
#include "ui_lyrics_out.h"

//Класс служит для вывода текста пенси (графический интерфейс)
//На вход подается строка, содержаящая сам текст

lyrics_out::lyrics_out(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::lyrics_out)
{
    ui->setupUi(this);

    this->setGeom("Lyrics");

    this->setWindowFlags(Qt::WindowStaysOnTopHint  );//Флаги окна виндоус
    this->DrawGUI();
    ui->lyrics_text_browser->verticalScrollBar()->setSingleStep(4);

     this->setRoundedCorners(6,6,6,6);

    this->setWindowOpacity(0);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(0.95);
    animation->start();

    Loading.setParent(this);
}

lyrics_out::~lyrics_out()
{
    delete ui;
}

void lyrics_out::out_Text_Song(QString text)                      //Печатает текст пенси
{
    Loading.hide();
    emit complete_recieving();
    ui->lyrics_text_browser->setText(text);
}

void lyrics_out::on_CloseApp_clicked()                            //Заурытие окна с текстом песни
{
    this->saveGeom("Lyrics");
    emit close_lyrics(true);
    this->close();
    delete this;
}


void lyrics_out::DrawGUI()                                        //Рисование интерфейса
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    int r = settings->value("Color/R").toInt();
    int g = settings->value("Color/G").toInt();
    int b = settings->value("Color/B").toInt();
    QString styleSheet = "lyrics_out { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(r).arg(g).arg(b));

    ui->CloseApp->setStyleSheet("border-image: url(:/new/prefix1/icons/close.gif) stretch;");

    QString stylesheet_path("://CSS/TextEdit.txt");
    ui->lyrics_text_browser->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    ui->Title->setStyleSheet(
                "color:white;"
                );

    ui->Icon->setStyleSheet("border-image: url(:/new/prefix1/vk.ico) stretch;");

    Loading.setStyleSheet(
                "border: 0px solid ;"
                "border-radius: 7px;"
                );
    Loading.setGeometry(120,100,17,17);
    QMovie *movie = new QMovie(":/new/prefix1/icons/loading32.gif");
    Loading.setMovie(movie);
    movie->start();
}
