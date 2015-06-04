#include "auther.h"
#include "ui_auther.h"
#include "widget.h"
#include "helloy.h"
#include "messages.h"

//Класс служит для авторизации пользователя
//При запуске открывает браузер с страницей авторизации вконтакте
//При правильном вооде лог-паса происходит редирект страницы, и новый url отправляется в класс vk_auth для парсинга
//и возвращает токен и айди пользователя. Данный класс создает главное окно и передает в него полученный токен и айди
//и завершается.
//Если авторизация уже проводилась ранее. Данный класс отправляет классу vk_auth запрос на проверку правильности токена
//И если токен правильный запускает сам плеер, при этом сам класс не показывает свою форму.

auther::auther(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::auther)
{

    ui->setupUi(this);   


    //SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    //SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);


    Hell = new helloy;
    //this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint |  Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint  );//Флаги окна виндоус
    this->DownloadSettings();
   // this->setAttribute(Qt::WA_DeleteOnClose);

    auth = new VkAuth();
    QThread *thread = new QThread(this);
    auth->moveToThread(thread);
    thread->start();
    Hell->show();

    connect(auth, SIGNAL(auth_error(bool)),this,SLOT(print_auth_erroR(bool)));
    connect(auth, SIGNAL(auth_success(QString,QString)),this, SLOT(run_player(QString, QString)));
    connect(auth, SIGNAL(connect_error(bool)), this, SLOT(print_auth_erroR(bool)));

    this->DrawGUI();
    this->setRoundedCorners(6,6,6,6);

    this->setWindowOpacity(0);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(800);
    animation->setStartValue(0);
    animation->setEndValue(TR);
    animation->start();
}

auther::~auther()
{
    delete ui;
}

void auther::print_auth_erroR(bool val)                                //Печатает ошибку авторизации
{
    ui->web_auth->load(QUrl("https://oauth.vk.com/authorize?client_id=4033129&scope=offline,friends,status,messages,wall,audio,groups&redirect_uri=https://oauth.vk.com/blank.html&display=wap&response_type=token"));
    connect(ui->web_auth, SIGNAL(urlChanged(QUrl)),auth,SLOT(check_url(QUrl)));

    Messages * messages = new Messages;
    QString title, text;

    if(val)
    {
        Hell->close();
        this->setGeom("Auther");
        this->show();

        title = "Авторизация";
        text = "Нет доступа к Интернету. Возможно у Вас отсутствует OpenSSL. Скачать?";
        messages->set_Title_and_Text(title, text, true, false);
        messages->show();
    }
    else
    {
        Hell->close();
        this->setGeom("Auther");
        this->show();

        title = "Авторизация";
        text = "Введите Логин и Пароль";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
    }
}

void auther::run_player(QString token, QString Id)                                              //Запуск самого плеера
{
    disconnect(ui->web_auth, SIGNAL(urlChanged(QUrl)),auth,SLOT(check_url(QUrl)));

        Widget * w = new Widget();

        this->hide();

        w->show();
        QString styleSheet = "Widget {background-color : rgb(%1, %2, %3);} ";
        w->setStyleSheet(styleSheet.arg(R).arg(G).arg(B));

        //Добавить кнопку в превью окна в панели задач
        w->Create_Thumb_Button();
        Hell->close();
        w->getTokenAndUsID(token, Id);

        this->saveGeom("Auther");
        this->close();
}

void auther::on_CloseApp_clicked()                                     //Обработка нажатия на кнопку закрыть
{
    this->saveGeom("Auther");
    exit(0);
}

void auther::on_hideApp_clicked()                                      //Обработка нажатия на кнопку свернуть
{
    this->showMinimized();
}


void auther::chech_auth()                                              //Запрос на проверку валидность токена и айди
{
    auth->readToken();
}

void auther::DownloadSettings()                                        //Зарузка файла settings.conf
{

            QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

            if(settings->value("About/Name").isNull())
                settings->setValue("About/Name", "VKPlayer");
            if(settings->value("About/Version").isNull())
                settings->setValue("About/Version", "221");
            if(settings->value("Color/B").isNull())
                settings->setValue("Color/B", "49");
            if(settings->value("Color/G").isNull())
                settings->setValue("Color/G", "49");
            if(settings->value("Color/R").isNull())
                settings->setValue("Color/R", "49");

            if(settings->value("TokenAndId/Id").isNull())
                settings->setValue("TokenAndId/Id", "111111");
            if(settings->value("TokenAndId/Token").isNull())
                settings->setValue("TokenAndId/Token", "11111111111111111111111");

            if(settings->value("Update/Val").isNull())
                settings->setValue("Update/Val", "0");

            if(settings->value("Volume/val").isNull())
                settings->setValue("Volume/val", "84");
            if(settings->value("WindowOpacity/tran").isNull())
                settings->setValue("WindowOpacity/tran", "0.96");
            if(settings->value("TextSongSpeed/val").isNull())
                settings->setValue("TextSongSpeed/val", "3");
            if(settings->value("Show_Notification/val").isNull())
                settings->setValue("Show_Notification/val", true);
            if(settings->value("Status_Enable/val").isNull())
                settings->setValue("Status_Enable/val", "0");
            if(settings->value("Hide_To_Tray/val").isNull())
                settings->setValue("Hide_To_Tray/val", true);
            if(settings->value("Directory/string").isNull())
                settings->setValue("Directory/string", " ");

            if(settings->value("HotKey_Play/id_HotKey").isNull())
                settings->setValue("HotKey_Play/id_HotKey", "0");
            if(settings->value("HotKey_Play/id_One_Key").isNull())
                settings->setValue("HotKey_Play/id_One_Key", "1");
            if(settings->value("HotKey_Play/id_Two_Key").isNull())
                settings->setValue("HotKey_Play/id_Two_Key", "36");
            if(settings->value("HotKey_Play/Key_Name").isNull())
                settings->setValue("HotKey_Play/Key_Name", "Alt + Home");

            if(settings->value("HotKey_Next/id_HotKey").isNull())
                settings->setValue("HotKey_Next/id_HotKey", "1");
            if(settings->value("HotKey_Next/id_One_Key").isNull())
                settings->setValue("HotKey_Next/id_One_Key", "1");
            if(settings->value("HotKey_Next/id_Two_Key").isNull())
                settings->setValue("HotKey_Next/id_Two_Key", "33");
            if(settings->value("HotKey_Next/Key_Name").isNull())
                settings->setValue("HotKey_Next/Key_Name", "Alt + PageUp");

            if(settings->value("HotKey_Previous/id_HotKey").isNull())
                settings->setValue("HotKey_Previous/id_HotKey", "2");
            if(settings->value("HotKey_Previous/id_One_Key").isNull())
                settings->setValue("HotKey_Previous/id_One_Key", "1");
            if(settings->value("HotKey_Previous/id_Two_Key").isNull())
                settings->setValue("HotKey_Previous/id_Two_Key", "34");
            if(settings->value("HotKey_Previous/Key_Name").isNull())
                settings->setValue("HotKey_Previous/Key_Name", "Alt + PageDown");

            if(settings->value("HotKey_Add/id_HotKey").isNull())
                settings->setValue("HotKey_Add/id_HotKey", "3");
            if(settings->value("HotKey_Add/id_One_Key").isNull())
                settings->setValue("HotKey_Add/id_One_Key", "1");
            if(settings->value("HotKey_Add/id_Two_Key").isNull())
                settings->setValue("HotKey_Add/id_Two_Key", "65");
            if(settings->value("HotKey_Add/Key_Name").isNull())
                settings->setValue("HotKey_Add/Key_Name", "Alt + A");

            if(settings->value("HotKey_Download/id_HotKey").isNull())
                settings->setValue("HotKey_Download/id_HotKey", "4");
            if(settings->value("HotKey_Download/id_One_Key").isNull())
                settings->setValue("HotKey_Download/id_One_Key", "1");
            if(settings->value("HotKey_Download/id_Two_Key").isNull())
                settings->setValue("HotKey_Download/id_Two_Key", "68");
            if(settings->value("HotKey_Download/Key_Name").isNull())
                settings->setValue("HotKey_Download/Key_Name", "Alt + D");

            if(settings->value("HotKey_VolumeUp/id_HotKey").isNull())
                settings->setValue("HotKey_VolumeUp/id_HotKey", "5");
            if(settings->value("HotKey_VolumeUp/id_One_Key").isNull())
                settings->setValue("HotKey_VolumeUp/id_One_Key", "1");
            if(settings->value("HotKey_VolumeUp/id_Two_Key").isNull())
                settings->setValue("HotKey_VolumeUp/id_Two_Key", "79");
            if(settings->value("HotKey_VolumeUp/Key_Name").isNull())
                settings->setValue("HotKey_VolumeUp/Key_Name", "Alt + O");

            if(settings->value("HotKey_VolumeDown/id_HotKey").isNull())
                settings->setValue("HotKey_VolumeDown/id_HotKey", "6");
            if(settings->value("HotKey_VolumeDown/id_One_Key").isNull())
                settings->setValue("HotKey_VolumeDown/id_One_Key", "1");
            if(settings->value("HotKey_VolumeDown/id_Two_Key").isNull())
                settings->setValue("HotKey_VolumeDown/id_Two_Key", "73");
            if(settings->value("HotKey_VolumeDown/Key_Name").isNull())
                settings->setValue("HotKey_VolumeDown/Key_Name", "Alt + P");


            settings->sync();

    R = settings->value("Color/R").toInt();
    G = settings->value("Color/G").toInt();
    B = settings->value("Color/B").toInt();
    TR = settings->value("WindowOpacity/tran").toFloat();

    QString styleSheet = "auther { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(R).arg(G).arg(B));
}

void auther::DrawGUI()                                                 //Рисует интерфейс окна авторизации
{
    ui->hideApp->setStyleSheet("border-image: url(:/new/prefix1/icons/down.gif) stretch;");
    ui->CloseApp->setStyleSheet("border-image: url(:/new/prefix1/icons/close.gif) stretch;");
    ui->logo->setStyleSheet("border-image: url(:/new/prefix1/icons/logo.png) stretch;");
}
