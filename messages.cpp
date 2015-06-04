#include "messages.h"
#include "ui_messages.h"
#include <QSettings>
#include <QDesktopServices>
#include <QPainter>

Messages::Messages(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::Messages)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    this->DrawGUI();

    this->setRoundedCorners(6,6,6,6);

    this->setWindowOpacity(0);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(0.99);
    animation->start();
}

Messages::~Messages()
{
    delete ui;
}


void Messages::on_Ok_Button_clicked()
{
    emit click_Ok();
    this->close();
    delete this;
}

void Messages::on_Download_Button_clicked()
{
    QDesktopServices::openUrl(QUrl("http://slproweb.com/products/Win32OpenSSL.html"));

    this->close();
    delete this;
}

void Messages::on_CloseApp_clicked()
{
    this->close();
    delete this;
}

void Messages::set_Title_and_Text(QString title, QString Text, bool Show_DB, bool Show_ReWrite)
{
    if(Show_DB){
       ui->Download_Button->show();
    }
    else
        ui->Download_Button->hide();

    if(Show_ReWrite){
        ui->Ok_Button->setText("Отмена");
        ui->ReWrite->show();
    }
    else
        ui->ReWrite->hide();

    ui->Title->setText(title);
    ui->Text->setText(Text);
    ui->Text->setAlignment(Qt::AlignCenter);
}

void Messages::DrawGUI()
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    int r = settings->value("Color/R").toInt();
    int g = settings->value("Color/G").toInt();
    int b = settings->value("Color/B").toInt();
    QString styleSheet = "Messages { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(r).arg(g).arg(b));

    ui->CloseApp->setStyleSheet("border-image: url(:/new/prefix1/icons/close.gif) stretch;");

    QString stylesheet_path;

    stylesheet_path =  "://CSS/MessageText.txt";
    ui->Text->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Button.txt";
    ui->Ok_Button->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->ReWrite->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->Download_Button->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    ui->Title->setStyleSheet(
                "color:white;"
                );

    ui->Icon->setStyleSheet("border-image: url(:/new/prefix1/icons/vkp2.ico) stretch;");
}


void Messages::on_ReWrite_clicked()
{
    emit click_ReWrite();
    this->close();
    delete this;
}
