
//Класс настроек плеера
//Имеет вкладки (общие, цвет окна, горячие клавиши, обновления, about)
//Вкладка общие: Две кнопки : Папка загрузки и выход из аккаунта

//Вкладка цвет окна: регулировка цвета плеера (r,g,b), прозрачность, кнопки: случайный цвет и стандартный
//При изменении любого из цвета или прозрачности, цвет автоматически меняется и в окне настроек и в главном окне
//При закрытие окна настроек все параметры автоматически сохраняются

//Вкладка горячие клавиши: Только отображение какие сочетания клавиш за что отвечают

//Вкладка обновления: Статус текущей версии, кнопка обновление (доступная если есть новая версия),
//кнопка проверить обовление

//Вкладка About: отображение версии плеера, разработчика и кнопка перехода на сайт

#include "settings.h"
#include "ui_settings.h"
#include "widget.h"
#include<cstdlib>
#include<ctime>

Settings::Settings(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    this->setGeom("Settings");

    this->setWindowFlags(Qt::WindowStaysOnTopHint );//Флаги окна виндоус

    this->DrawGUI();
    this->DownloadSettings();

    ui->horizontalSlider_R->setValue(r);
    ui->horizontalSlider_G->setValue(g);
    ui->horizontalSlider_B->setValue(b);

    connect(ui->horizontalSlider_R,SIGNAL(valueChanged(int)),this,SLOT(sendValueR(int)));
    connect(ui->horizontalSlider_G,SIGNAL(valueChanged(int)),this,SLOT(sendValueG(int)));
    connect(ui->horizontalSlider_B,SIGNAL(valueChanged(int)),this,SLOT(sendValueB(int)));
    connect(ui->transparency_Slider,SIGNAL(valueChanged(int)),this,SLOT(sendTransparency(int)));
    connect(ui->spinBox_Text_Song, SIGNAL(valueChanged(int)),this, SLOT(Save_SpeedSOngText(int)));
    connect(ui->checkBox_Notification, SIGNAL(toggled(bool)),this, SIGNAL(ChangeNotification(bool)));
    connect(ui->checkBox_Hide_Tray, SIGNAL(toggled(bool)), this, SIGNAL(ChangeHideToTray(bool)));
    connect(ui->Search_lyrics_only, SIGNAL(toggled(bool)), this, SLOT(Save_Search_options()));
    connect(ui->Search_performer_only, SIGNAL(toggled(bool)), this, SLOT(Save_Search_options()));
    connect(ui->Search_user_only, SIGNAL(toggled(bool)), this, SLOT(Save_Search_options()));
    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), //Выбор сочетания клавиш
            this, SLOT(selectedItem(QTableWidgetItem*)));
    connect(ui->aboutQt, SIGNAL(clicked()), QApplication::instance(), SLOT(aboutQt()));


    this->setRoundedCorners(6,6,6,6);

    this->setWindowOpacity(0);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(tran);
    animation->start();


}

Settings::~Settings()
{
    delete ui;
}

bool Settings::eventFilter(QObject* watched, QEvent* event){
    if (watched == ui->horizontalSlider_R && event->type() == QEvent::MouseButtonRelease )
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            ui->horizontalSlider_R->setValue(QStyle::sliderValueFromPosition(ui->horizontalSlider_R->minimum(), ui->horizontalSlider_R->maximum(), mouseEvent->x(), ui->horizontalSlider_R->width()));
        }
    if (watched == ui->horizontalSlider_G && event->type() == QEvent::MouseButtonRelease )
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            ui->horizontalSlider_G->setValue(QStyle::sliderValueFromPosition(ui->horizontalSlider_G->minimum(), ui->horizontalSlider_G->maximum(), mouseEvent->x(), ui->horizontalSlider_G->width()));
        }

    if (watched == ui->horizontalSlider_B && event->type() == QEvent::MouseButtonRelease )
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            ui->horizontalSlider_B->setValue(QStyle::sliderValueFromPosition(ui->horizontalSlider_B->minimum(), ui->horizontalSlider_B->maximum(), mouseEvent->x(), ui->horizontalSlider_B->width()));
        }

    if (watched == ui->transparency_Slider && event->type() == QEvent::MouseButtonRelease )
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            ui->transparency_Slider->setValue(QStyle::sliderValueFromPosition(ui->transparency_Slider->minimum(), ui->transparency_Slider->maximum(), mouseEvent->x(), ui->transparency_Slider->width()));
        }
        return false;
}


void Settings::MenuChooseDirectory()                                  //Выбор директории загрузки файла
{
    QString directory;
    directory = QFileDialog::getExistingDirectory(this, tr("Выбрать папку"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
    settings->setValue("Directory/string", directory);
    emit Directory(directory);
}

void Settings::DrawGUI()                                              //Рисование GUI
{   
    QString stylesheet_path;

    stylesheet_path = "://CSS/TabWidget.txt";
    ui->tabWidget->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/HorizontalSlider.txt";
    ui->horizontalSlider_B->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->horizontalSlider_G->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->horizontalSlider_R->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->transparency_Slider->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    ui->horizontalSlider_R->installEventFilter(this);
    ui->horizontalSlider_G->installEventFilter(this);
    ui->horizontalSlider_B->installEventFilter(this);
    ui->transparency_Slider->installEventFilter(this);

    stylesheet_path = "://CSS/TableWidget.txt";
    ui->tableWidget->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Label.txt";
    ui->label->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_2->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_3->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_5->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->printActualVersion->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->textBrowser->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_6->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_7->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_8->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_9->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_10->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->label_11->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Button.txt";
    ui->Download_Dir_BTN->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->Exit_account->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->Random_Color->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->StandartColor->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->Open_Site_BTN->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->UpdateOLD->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->CheckNewVER->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->aboutQt->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->Default_HotKey->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/SpinBox.txt";
    ui->spinBox_Text_Song->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path =  "://CSS/MessageText.txt";
    ui->WarningUpdate->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->Text->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    ui->Title->setStyleSheet(
                "color:white;"
                );

    ui->Icon->setStyleSheet("border-image: url(:/new/prefix1/icons/vkp2.ico) stretch;");
    ui->CloseApp->setStyleSheet("border-image: url(:/new/prefix1/icons/close.gif) stretch;");

    ui->tableWidget->setEditTriggers(NULL);
}

void Settings::on_Download_Dir_BTN_clicked()                          //Нажатие кнопки выбора папки загрузки
{
    QRect rect = ui->Download_Dir_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Download_Dir_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+65, Y+15, 1, 1));
     animation->setEndValue(QRect(X, Y, 130, 30));
     animation->start();
    this->MenuChooseDirectory();
}

void Settings::on_Exit_account_clicked()                              //Обработка нажатия на кнопку выхода из аккаунта
{

    QRect rect = ui->Exit_account->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Exit_account, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+65, Y+15, 1, 1));
     animation->setEndValue(QRect(X, Y, 130, 30));
     animation->start();

    QString token = "1111111111111111111111111111";
    QString UserId = "11111111111";

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    settings->setValue("TokenAndId/Token", token);
    settings->setValue("TokenAndId/Id", UserId);
    settings->sync();

    this->saveGeom("Settings");
    this->close();
    emit exit_ACC();
}


void Settings::sendValueR(int R)                                      //ПРименить красный цвет
{
    r = R;
    QString styleSheet = "Settings { background-color : rgb(%1, %2, %3)}";
    int a,d,c;
    a = r -25;
    d = g -25;
    c = b -25;
    if(a < 1)
        a = 0;
    if(d < 1)
        d = 0;
    if(c < 1)
        c = 0;
    this->setStyleSheet(styleSheet.arg(a).arg(d).arg(c));
    emit valueR(r);
}

void Settings::sendValueG(int G)                                      //Применить зеленый цвет
{
    g = G;
    QString styleSheet = "Settings { background-color : rgb(%1, %2, %3)}";
    int a,d,c;
    a = r -25;
    d = g -25;
    c = b -25;
    if(a < 1)
        a = 0;
    if(d < 1)
        d = 0;
    if(c < 1)
        c = 0;
    this->setStyleSheet(styleSheet.arg(a).arg(d).arg(c));
    emit valueG(g);
}

void Settings::sendValueB(int B)                                      //ПРименить синий цвет
{
    b = B;
    QString styleSheet = "Settings { background-color : rgb(%1, %2, %3)}";
    int a,d,c;
    a = r -25;
    d = g -25;
    c = b -25;
    if(a < 1)
        a = 0;
    if(d < 1)
        d = 0;
    if(c < 1)
        c = 0;
    this->setStyleSheet(styleSheet.arg(a).arg(d).arg(c));
    emit valueB(b);
}

void Settings::sendTransparency(int value)                            //ПРименить прозрачность
{
    tran = value;
    tran = tran/100;
    this->setWindowOpacity(tran);
    emit Transpar(value);
}

void Settings::on_StandartColor_clicked()                             //Обработка нажатия на кнопку стандратный цвет
{
    QRect rect = ui->StandartColor->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->StandartColor, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+45, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 90, 20));
     animation->start();

    b = r = g = 49;
    ui->horizontalSlider_R->setValue(49);
    ui->horizontalSlider_G->setValue(49);
    ui->horizontalSlider_B->setValue(49);
    emit standartC();
}

void Settings::on_Random_Color_clicked()                              //Оюработка нажатия на случайный цвет
{
    QRect rect = ui->Random_Color->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Random_Color, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+45, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 90, 20));
     animation->start();

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    r = qrand() % 254;
    g = qrand() % 254;
    b = qrand() % 254;

    ui->horizontalSlider_R->setValue(r);
    ui->horizontalSlider_G->setValue(g);
    ui->horizontalSlider_B->setValue(b);
}

void Settings::on_CloseApp_clicked()                                  //Выход из настроек
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    settings->setValue("Color/R", r);
    settings->setValue("Color/G", g);
    settings->setValue("Color/B", b);
    settings->setValue("WindowOpacity/tran", QString::number(tran));
    settings->setValue("Update/Val", valupdate);
    settings->sync();

    this->saveGeom("Settings");
    emit sEnabled(true);
    delete this;
}

void Settings::on_Open_Site_BTN_clicked()                             //Открытие сайта плеера
{
    QRect rect = ui->Open_Site_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Open_Site_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+65, Y+15, 1, 1));
     animation->setEndValue(QRect(X, Y, 130, 30));
     animation->start();

    QDesktopServices::openUrl(QUrl("http://playervk.ru"));

    this->saveGeom("Settings");
    emit sEnabled(true);
    delete this;
}

void Settings::printNewVersion(bool val)                              //Вывод доступности новой версии
{
    if(val)
    {
       ui->printActualVersion->clear();
       ui->printActualVersion->setText("Доступна новая версия!");
       ui->UpdateOLD->show();
       ui->WarningUpdate->show();
    }
    else
    {
        ui->printActualVersion->clear();
        ui->printActualVersion->setText("У Вас Актуальная версия");
        ui->UpdateOLD->hide();
        ui->WarningUpdate->hide();
    }

}

void Settings::printErrorUpdating(bool val)                           //Вывод ошибки подключений к серверу обновлений
{
    ui->printActualVersion->clear();
    ui->printActualVersion->setText("Проблемы с сервером обновлений(");
    ui->UpdateOLD->hide();
    ui->WarningUpdate->hide();
}

void Settings::DownloadSettings()                                     //Загрузка файла settings.txt
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    r = settings->value("Color/R").toInt();
    g = settings->value("Color/G").toInt();
    b = settings->value("Color/B").toInt();
    tran = settings->value("WindowOpacity/tran").toFloat();
    valupdate = settings->value("Update/Val").toInt();
    ui->spinBox_Text_Song->setValue(settings->value("TextSongSpeed/val").toInt());
    ui->checkBox_Notification->setChecked(settings->value("Show_Notification/val").toBool());
    ui->Search_lyrics_only->setChecked(settings->value("Search_lyrics_only/val").toBool());
    ui->Search_performer_only->setChecked(settings->value("Search_performer_only/val").toBool());
    ui->Search_user_only->setChecked(settings->value("Search_user_only/val").toBool());
    ui->checkBox_Hide_Tray->setChecked(settings->value("Hide_To_Tray/val").toBool());

     if(valupdate == 1)
     {
        ui->printActualVersion->clear();
        ui->printActualVersion->setText("Доступна новая версия!");
        ui->UpdateOLD->show();
        ui->WarningUpdate->show();
     }
     else
     {
         ui->printActualVersion->clear();
         ui->printActualVersion->setText("У Вас Актуальная версия");
         ui->UpdateOLD->hide();
         ui->WarningUpdate->hide();
      }

        QString styleSheet = "Settings { background-color : rgb(%1, %2, %3)}";
        int a,d,c;
        a = r -25;
        d = g -25;
        c = b -25;
        if(a < 1)
            a = 0;
        if(d < 1)
            d = 0;
        if(c < 1)
            c = 0;
        this->setStyleSheet(styleSheet.arg(a).arg(d).arg(c));
        this->setWindowOpacity(tran);
        float tmpT = tran;
        tmpT = tmpT*100;
        int tmp = tmpT;
        ui->transparency_Slider->setValue(tmp);

        ui->tableWidget->item(0,0)->setText(settings->value("HotKey_Play/Key_Name").toString());
        ui->tableWidget->item(1,0)->setText(settings->value("HotKey_Next/Key_Name").toString());
        ui->tableWidget->item(2,0)->setText(settings->value("HotKey_Previous/Key_Name").toString());
        ui->tableWidget->item(3,0)->setText(settings->value("HotKey_Add/Key_Name").toString());
        ui->tableWidget->item(4,0)->setText(settings->value("HotKey_Download/Key_Name").toString());
        ui->tableWidget->item(5,0)->setText(settings->value("HotKey_VolumeUp/Key_Name").toString());
        ui->tableWidget->item(6,0)->setText(settings->value("HotKey_VolumeDown/Key_Name").toString());

        settings->sync();
        delete settings;
}

void Settings::Save_SpeedSOngText(int val)
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
    settings->setValue("TextSongSpeed/val", val);
    settings->sync();
    emit ChangeSpeedText(val);
}

void Settings::selectedItem(QTableWidgetItem * item)
{
    this->setEnabled(false);
    Registration_Key * register_key = new Registration_Key();
    connect(register_key, SIGNAL(send_HotKey(QString, QString, int, int, int)),
            this, SLOT(apply_new_HotKey(QString, QString, int, int, int)));
    connect(register_key, SIGNAL(sendEnabler(bool)), this, SLOT(setEnabled(bool)));
    register_key->Recieve_data(item->row(), item->text());
            register_key->show();
}

void Settings::apply_new_HotKey(QString key_one, QString key_two, int id_key_one, int id_key_two, int row)
{
    ui->tableWidget->item(row,0)->setSelected(false);
    qDebug()<<key_two << " " << key_one << "" << row;
    emit send_new_hotkey(row, id_key_one, id_key_two);
    ui->tableWidget->item(row, 0)->setText(key_one + " + " + key_two);
}

void Settings::Save_Search_options()
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
    settings->setValue("Search_lyrics_only/val", ui->Search_lyrics_only->isChecked());
    settings->setValue("Search_performer_only/val", ui->Search_performer_only->isChecked());
    settings->setValue("Search_user_only/val", ui->Search_user_only->isChecked());
    settings->sync();
}


void Settings::on_CheckNewVER_clicked()                               //Обработка нажатия на кнопку проверить оновления
{
    QRect rect = ui->CheckNewVER->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->CheckNewVER, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+65, Y+15, 1, 1));
     animation->setEndValue(QRect(X, Y, 130, 30));
     animation->start();

    ui->printActualVersion->clear();
    ui->printActualVersion->setText("Поиск...");
    UpdateVersion * Update = new UpdateVersion(this);
    connect(Update, SIGNAL(NewVersionFound(bool)), this, SLOT(printNewVersion(bool)));
    connect(Update, SIGNAL(ErrorSignal(bool)), this, SLOT(printErrorUpdating(bool)));
    Update->StartCheck();                                       //Запуск проверки на наличие обновлений
}

void Settings::on_UpdateOLD_clicked()                                 //Обработка нажатия на кнопку "Обновить"
{
    QRect rect = ui->UpdateOLD->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->UpdateOLD, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+65, Y+15, 1, 1));
     animation->setEndValue(QRect(X, Y, 130, 30));
     animation->start();

    this->saveGeom("Settings");
    emit StartDownloadNewVersion();
    emit sEnabled(true);
    delete this;


}

void Settings::on_Default_HotKey_clicked()
{
    QRect rect = ui->Default_HotKey->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Default_HotKey, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+35, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 70, 20));
     animation->start();

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

        settings->setValue("HotKey_Play/id_HotKey", "0");
        settings->setValue("HotKey_Play/id_One_Key", "1");
        settings->setValue("HotKey_Play/id_Two_Key", "36");
        settings->setValue("HotKey_Play/Key_Name", "Alt + Home");
        emit send_new_hotkey(0, 1, 36);
        ui->tableWidget->item(0,0)->setText("Alt + Home");

        settings->setValue("HotKey_Next/id_HotKey", "1");
        settings->setValue("HotKey_Next/id_One_Key", "1");
        settings->setValue("HotKey_Next/id_Two_Key", "33");
        settings->setValue("HotKey_Next/Key_Name", "Alt + PageUp");
        emit send_new_hotkey(1, 1, 33);
        ui->tableWidget->item(1,0)->setText("Alt + PageUp");

        settings->setValue("HotKey_Previous/id_HotKey", "2");
        settings->setValue("HotKey_Previous/id_One_Key", "1");
        settings->setValue("HotKey_Previous/id_Two_Key", "34");
        settings->setValue("HotKey_Previous/Key_Name", "Alt + PageDown");
        emit send_new_hotkey(2, 1, 34);
        ui->tableWidget->item(2,0)->setText("Alt + PageDown");

        settings->setValue("HotKey_Add/id_HotKey", "3");
        settings->setValue("HotKey_Add/id_One_Key", "1");
        settings->setValue("HotKey_Add/id_Two_Key", "65");
        settings->setValue("HotKey_Add/Key_Name", "Alt + A");
        emit send_new_hotkey(3, 1, 65);
        ui->tableWidget->item(3,0)->setText("Alt + A");

        settings->setValue("HotKey_Download/id_HotKey", "4");
        settings->setValue("HotKey_Download/id_One_Key", "1");
        settings->setValue("HotKey_Download/id_Two_Key", "68");
        settings->setValue("HotKey_Download/Key_Name", "Alt + D");
        emit send_new_hotkey(4, 1, 68);
        ui->tableWidget->item(4,0)->setText("Alt + D");

        settings->setValue("HotKey_VolumeUp/id_HotKey", "5");
        settings->setValue("HotKey_VolumeUp/id_One_Key", "1");
        settings->setValue("HotKey_VolumeUp/id_Two_Key", "79");
        settings->setValue("HotKey_VolumeUp/Key_Name", "Alt + O");
        emit send_new_hotkey(5, 1, 79);
        ui->tableWidget->item(5,0)->setText("Alt + O");

        settings->setValue("HotKey_VolumeDown/id_HotKey", "6");
        settings->setValue("HotKey_VolumeDown/id_One_Key", "1");
        settings->setValue("HotKey_VolumeDown/id_Two_Key", "73");
        settings->setValue("HotKey_VolumeDown/Key_Name", "Alt + I");
        emit send_new_hotkey(6, 1, 73);
        ui->tableWidget->item(6,0)->setText("Alt + I");

        settings->sync();
}
