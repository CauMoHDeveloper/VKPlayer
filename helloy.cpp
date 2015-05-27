#include "helloy.h"
#include "ui_helloy.h"

//Этот класс имет графический интерефейс
//Отображает только название программы во время загрузки основного окна

helloy::helloy(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::helloy)
{
    ui->setupUi(this);
     this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint |  Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint  );//Флаги окна виндоус
     QString styleSheet = "helloy { background-color : rgb(49, 49, 49)}";
     this->setStyleSheet(styleSheet);
     this->setWindowOpacity(0.86);
     //this->setAttribute(Qt::WA_DeleteOnClose);
    ui->logo->setStyleSheet("border-image: url(:/new/prefix1/icons/logo.png) stretch;");
    this->setRoundedCorners(8,8,8,8);
}

helloy::~helloy()
{
    delete ui;
}
