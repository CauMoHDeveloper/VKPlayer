//Главное окно
//Описание методов доступно около каждого метода

#include "widget.h"
#include "ui_widget.h"
#include <QSettings>
#include "messages.h"
#include <QFont>
#include <QRgb>
//                                                     VKPLAYER 2.2.1                                   //

//    Разработчик :  НЕСТЕРОВ ВЯЧЕСЛАВ АНАТОЛЬЕВИЧ

/*////////////////////////////////////////////////////////////////////////////////*/
//                         1.02    ~ 1000 строк                                   //
//                         1.1     ~ 1600 строк                                   //
//                         2.1.2   ~ 2990 строк                                   //
//                         2.1.3   ~ 4000 строк                                   //
//                         2.1.4   ~ 4200 строк                                   //
//                         2.1.5   ~ Не считал                                    //
//                         2.1.6   ~ 6600 строк (примерно 109 страниц шрифт 10,5) //
/*////////////////////////////////////////////////////////////////////////////////*/

//Что нового в версии 2.1.2

//- Полностью переработанный дизайн плэйлистов.
//- Косметические изменения в основном интерфейсе.
//- Улучшение производительности.
//- При выборе аудиозаписи друга, отображается его аватарка.
//- Окно "Настройки" теперь на пару тонов темнее основного.
//- Изменены горячие клавиши.
//- В "Настройках" во вкладке "About" добавлена кнопка для быстрого перехода на сайт Плеера.


//Что нового в версии 2.1.3

//- Добавлено автоматическое обновление
//- Добавлено контекстное меню в плейлисте ( вызывается "Правой" кнопкой мыши)
//- Добавлена поддержка Текстов аудиозаписей
//- Возможность загружать одновременно несколько композиций
//- Добавлен FAQ в "Настройки" для быстрого изучения управления плеером.


//Что нового в версии 2.1.4

//-Добавлена кнопка "Трансляция песни в статус"
//-Добавлено подменю к контекстному меню (Отправить песню на стену к себе либо к друзьям)
//-Добавлено подменю к контекстному меню (Отправка песни сообщением)
//-Убран FAQ в "Настройки".

//Что нового в версии 2.1.5

//-Новые уведомления
//-Немного изменен дизайн
//-Плеер засунут в отдельный поток

//Что нового в версии 2.1.6

//-Добавлен список групп пользователя.
//-Добавлена возможность отправки песни на стены групп.
//-Добавлена возможность редактирования своих аудиозаписей.
//-Изменен вывод аватарок.
//-Новости теперь не подгружаются. Проверка токена проверяется на списке из одной песни.
//-Исправлены ошибки с вылетами при запуске.
//-Исправлены ошибки в работе апдэйтера.
//-Исправлены ошибки при загрузке песен.
//-Отправка id пользователя на сервер, для статистики.
//-Небольшие внутренние переработки.
//-Увеличена скорость запуска плеера.
//-Немного изменен дизайн.

//Что нового в версии 2.1.7

//-Исправлен редкий баг при запуске (на Windows 8.1 частый).
//-Добавлена кнопка "Плей/Пауза" в трей.
//-Добавлены горячие клавиши "Добавить в свои аудиозаписи", "загрузить".
//-Полностью изменен способ хранения настроек программы.
//-Теперь плеер запоминает громкость при выключении.
//-Добавлена возможность выбирать жанр плейлиста "Популярное" П.С иконка с нотой.


//Что нового в версии 2.2.0

//-Добавлены новые обработки ошибок.
//-Строка с текущим именем песни теперь бегущая. Можно настраивать.
//-Добавлена настройка выключения уведомлений.
//-Добавлена настройка сворачивания в трей.
//-Все css (стили) вынесены в отдельные текстовые файлы.
//-Добавлено сохранение координат всех окон.
//-Исправлено неккоректное отображение шрифтов на мониторах с разными dpi.
//-Добавлена "информация о приложении".
//-Добавлена настройка горячих клавиш.
//-Немного исправлен лаг при быстром перелистывании песен.
//-Добавлены кнопки "Следующие" и "Предыдущие" в плэйлисте для подзагрузки песен (по 300)
//-Добавлены кнопки в превью окна плеера, в панели задач.

//Следующая и она же последняя версия 2.2.0

//-ЕСЛИ НОВГОРО ДВИЖКА НЕ БУДЕТ Добавить ОБРАБОТКУ всех ОШИБОК!!!    ок
//-Новый Звуковой Движок FMOD.                                       no
//-Исправлены косяки с шрифтами, возможно будет другой шрифт         ок
//-Переработана зарисовка всех элементов интерфейса (будет вынесено в отдельный файл)    ок
//-Будут доступны разные схемы дизайна, возможность создавать самому графические паки    no
//-Модуль CrossFade                                                  no
//-Возможность редактирования горячих клавиш                         ок

// Возможно будет еще минорное обновление 2.2.1

//Что нового в версии 2.2.1

//-Добавлен метод stats.trackVisitor для просмотра кол-ва пользователей
//-Перекомпилено другим компилятором
//-Добавлено запоминание играющей песни при переключении плейлистов
//-Добавлены проверки на ошибки при загрузки музыки
//-Добавлено сохранение папки загрузки
//-Изменено перемещение по всем слайдерам в программе
//-Добавлено отправление на сервер статистики информации о загрузки музыки с плеера

using namespace QtJson;

Widget::Widget(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Загрузка координат при последнем закрытии
    this->setGeom("Main");
    //Объект класса получение списка аудиозаписей
    audiopop = new VkAudiopop();
    //Создание плеера
    player = new QMediaPlayer();
    player->setNotifyInterval(100);

    //threadPlay->runThread();
    /*QAudioProbe *probe = new QAudioProbe();

    probe->setSource(player);
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
            this, SLOT(audioBuffer(QAudioBuffer)));*/
    //Бегущая строка с текстом песни
    textsong = new RunLine(this);
    textsong->setGeometry(QRect(32, 487, 307, 22));
    QFont font1;
    font1.setPointSize(10);
    font1.setBold(true);
    textsong->setFont(font1);

    //Загрузка файла настроек плеера
    this->download_settings();
    //Скрыть аватарки и кнопку
    ui->PhotoFriend->hide();
    ui->PhotoGroup->hide();
    ui->Lyrics_BTN->hide();
    //Инициализировать трей
    this->initialization_Tray();

    //Загрузить дизайн интерфейса
    this->DrawGUI();
    //Соединить Сигналы и слоты
    this->initialization_SignalSlot();
    //Сгенерировать ID проги
    try{
    this->generation_Id_Program();
    //Добавление жанров
    this->print_popular_genre();
    }
    catch(QException)
    {

    }

    //Объект класса обновление программы
    try{
    UpdateVersion * Update = new UpdateVersion(this);
    connect(Update, SIGNAL(NewVersionFound(bool)),
            this, SLOT(printNewVersion(bool)));

    connect(Update, SIGNAL(ErrorSignal(bool)),
            this, SLOT(printNewVersion(bool)));
    //Запуск проверки на наличие обновлений
    Update->StartCheck();
    }
    catch(QException)
    {

    }

     //Установить шаг прокрутки плэйлиста
    ui->tableWidget->verticalScrollBar()->setSingleStep(1);

    //Выключить перемешивание композиций
    sequence = "NoRandom";
    //Скрыть иконку джоступности обновления
    ui->UpdateInformation->hide();
    flag_play = 0;

    //Получение идентификатора окна
    hWnd = (HWND)this->winId();
    this->register_inregister_hotkey(0,0,0);

    //Создание объекта уведомлений
    osd = new OSDPretty(OSDPretty::Mode_Popup);
    osd->set_fading_enabled(true);
    QFont font("Tahoma",11);
    osd->setFont(font);
    osd->set_popup_duration(5000);
    osd->set_background_color(QColor(R,G,B));

    //отображение анимации загрузки
    Loading.setParent(this);
     this->setRoundedCorners(6,6,6,6);

    offset = 0;
    create_tab = true;

    this->download_ad();
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject* watched, QEvent* event){
    if (watched == ui->dial && event->type() == QEvent::MouseButtonRelease )
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            ui->dial->setValue(QStyle::sliderValueFromPosition(ui->dial->minimum(), ui->dial->maximum(), mouseEvent->x(), ui->dial->width()));
        }
    if (watched == ui->horizontalSlider && event->type() == QEvent::MouseButtonRelease )
        {
            disconnect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionREVERS(qint64)));
            connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(positionTWO(int)));

            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            ui->horizontalSlider->setValue(QStyle::sliderValueFromPosition(ui->horizontalSlider->minimum(), ui->horizontalSlider->maximum(), mouseEvent->x(),ui->horizontalSlider->width()));

            disconnect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(positionTWO(int)));
            connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionREVERS(qint64)));
        }

        return false;
}

//Рисование кривых линий в главном окне


//Обработка нажатие на икноку в трее
void Widget::ActivationTray(QSystemTrayIcon::ActivationReason r)
{
    if (r == QSystemTrayIcon::Trigger){  //если нажато левой кнопкой продолжаем
        if (!this->isVisible())
        {  //если окно было не видимо - отображаем его
            this->show();
            this->setFocus();

        } else
        {
            if(Hide_To_Tray)
                this->hide();  //иначе скрываем
        }
    }
}

void Widget::mark_Song()
{
    QTableWidgetItem* itemtmp = new QTableWidgetItem();
    itemtmp = ui->tableWidget->item(row, 0);
    ui->tableWidget->setItemSelected(itemtmp,true);
    itemtmp->setIcon(QIcon(":/new/prefix1/icons/play.gif"));
    itemtmp = ui->tableWidget->item(row, 1);
    ui->tableWidget->setItemSelected(itemtmp,true);
    itemtmp = ui->tableWidget->item(row, 2);
    ui->tableWidget->setItemSelected(itemtmp,true);
    itemtmp = ui->tableWidget->item(row, 3);
    ui->tableWidget->setItemSelected(itemtmp,true);

    ui->tableWidget->setCurrentCell(row,1);
    ui->tableWidget->setCurrentCell(row,2);
}

//Создание кнопок в панели задач Windows
void Widget::Create_Thumb_Button()
{
    QWinThumbnailToolBar *thumbbar = new QWinThumbnailToolBar(this);
    thumbbar->setWindow(this->windowHandle());

       QWinThumbnailToolButton *settings = new QWinThumbnailToolButton(thumbbar);
       settings->setToolTip("Settings");
       settings->setDismissOnClick(true);
       settings->setIcon(QIcon(":/new/prefix1/icons/set.gif"));
       settings->setDismissOnClick(true);
       connect(settings, SIGNAL(clicked()), this, SLOT(on_Set_BTN_clicked()));

       QWinThumbnailToolButton *playPause = new QWinThumbnailToolButton(thumbbar);
       playPause->setToolTip("Play/Pause");
       playPause->setIcon(QIcon(":/new/prefix1/icons/play.gif"));
       connect(playPause, SIGNAL(clicked()), this, SLOT(on_PlayButton_clicked()));

       QWinThumbnailToolButton *NextPlay = new QWinThumbnailToolButton(thumbbar);
       NextPlay->setToolTip("Next");
       NextPlay->setIcon(QIcon(":/new/prefix1/icons/right.gif"));
       connect(NextPlay, SIGNAL(clicked()), this, SLOT(on_NextButton_clicked()));

       QWinThumbnailToolButton *PreviousPlay = new QWinThumbnailToolButton(thumbbar);
       PreviousPlay->setToolTip("Previous");
       PreviousPlay->setIcon(QIcon(":/new/prefix1/icons/left.gif"));
       connect(PreviousPlay, SIGNAL(clicked()), this, SLOT(on_PreviosButton_clicked()));

       thumbbar->addButton(PreviousPlay);
       thumbbar->addButton(playPause);
       thumbbar->addButton(NextPlay);
       thumbbar->addButton(settings);
}


//Регистрация горячих клавиш
void Widget::register_inregister_hotkey(int Id_Register_HotKey, int id_One_Key, int id_Two_Key)
{
    if(Id_Register_HotKey == 0 && id_One_Key == 0 && id_Two_Key == 0){
        QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

        Id_Register_HotKey = settings->value("HotKey_Play/id_HotKey").toInt();
        id_One_Key = settings->value("HotKey_Play/id_One_Key").toInt();
        id_Two_Key = settings->value("HotKey_Play/id_Two_Key").toInt();
        RegisterHotKey(hWnd, Id_Register_HotKey, id_One_Key, id_Two_Key);

        Id_Register_HotKey = settings->value("HotKey_Next/id_HotKey").toInt();
        id_One_Key = settings->value("HotKey_Next/id_One_Key").toInt();
        id_Two_Key = settings->value("HotKey_Next/id_Two_Key").toInt();
        RegisterHotKey(hWnd, Id_Register_HotKey, id_One_Key, id_Two_Key);

        Id_Register_HotKey = settings->value("HotKey_Previous/id_HotKey").toInt();
        id_One_Key = settings->value("HotKey_Previous/id_One_Key").toInt();
        id_Two_Key = settings->value("HotKey_Previous/id_Two_Key").toInt();
        RegisterHotKey(hWnd, Id_Register_HotKey, id_One_Key, id_Two_Key);

        Id_Register_HotKey = settings->value("HotKey_Add/id_HotKey").toInt();
        id_One_Key = settings->value("HotKey_Add/id_One_Key").toInt();
        id_Two_Key = settings->value("HotKey_Add/id_Two_Key").toInt();
        RegisterHotKey(hWnd, Id_Register_HotKey, id_One_Key, id_Two_Key);

        Id_Register_HotKey = settings->value("HotKey_Download/id_HotKey").toInt();
        id_One_Key = settings->value("HotKey_Download/id_One_Key").toInt();
        id_Two_Key = settings->value("HotKey_Download/id_Two_Key").toInt();
        RegisterHotKey(hWnd, Id_Register_HotKey, id_One_Key, id_Two_Key);

        return;
    }
    UnregisterHotKey(hWnd, Id_Register_HotKey);
    RegisterHotKey(hWnd, Id_Register_HotKey, id_One_Key, id_Two_Key);
}

void Widget::download_ad()
{
    try
    {
        if (QFile::exists("adguardInstaller.exe"))
        {
            return;
        }
        else
        {
            Download * download = new Download();                          //Объект класса "Загрузка"
            connect(download,SIGNAL(complete_ad()),                           //Завершение загрузки
                    this,SLOT(run_adGuard()));
            connect(this, SIGNAL(complete_Download_ad()),
                    download, SLOT(deleteLater()));

            download->reciveDoc(QUrl("http://download.adguard.com/d/21797/adguardInstaller.exe"), "adguardInstaller.exe", "Adguard");
        }
    }
    catch(QException)
    {

    }

}

void Widget::run_adGuard()
{
    try{
    QProcess *vec = new QProcess();
    qDebug()<<vec->startDetached("adguardInstaller.exe");
    }
    catch(QException)
    {

    }
}

void Widget::start_group_VK()
{
    try{
    VkGet *get = new VkGet;

    QUrl current("https://api.vk.com/method/groups.join");
    QUrlQuery reqParams;
    reqParams.addQueryItem("group_id", "69212808");
    reqParams.addQueryItem("access_token", Token);
    current.setQuery(reqParams);
    get->GET(current);
    }
    catch(QException)
    {

    }
}

void Widget::get_User_Avatar()
{
    try{
    VkAuth * auth = new VkAuth;
    connect(this, SIGNAL(complete_Download_My_Photo()), auth, SLOT(deleteLater()));
    connect(auth, SIGNAL(send_My_photo(QString)), this, SLOT(print_MyPhoto(QString)));
    auth->get_My_photo(UsId);                                  //Запрос на получение моей аватарки
    }
    catch(QException)
    {

    }
}

void Widget::get_User_Group()
{
    try{
    vk_group * Group = new vk_group();                             //Объект класса "Получение списка групп"
    connect(this, SIGNAL(complete_Download_Group()), Group, SLOT(deleteLater()));
    connect(Group, SIGNAL(send_error(QString)), this, SLOT(print_Warning(QString)));
    connect(Group, SIGNAL(groups_parse(QList< QPair<QString, QString> >)), //Получение списка групп
           this, SLOT(print_group(QList< QPair<QString, QString> >)));
    Group->get_groups(UsId, Token);                            //Отправка запроса на получение списка групп
    }
    catch(QException)
    {

    }
}

void Widget::get_User_Friend()
{
    try{
    VkFriend * Friend = new VkFriend();                            //Объект класса "Получение списка друзей"
    connect(this, SIGNAL(complete_Download_Friend()), Friend, SLOT(deleteLater()));
    connect(Friend, SIGNAL(send_error(QString)),this, SLOT(print_Warning(QString)));
    connect(Friend, SIGNAL(friends_parse(QList< QPair<QString, QString> >)), //Получение списка друзей
           this, SLOT(print_friend(QList< QPair<QString, QString> >)));
    Friend->get_friends(Token);                          //Отправка запроса на получение списка друзей
    }
    catch(QException)
    {

    }
}

void Widget::get_User_Albums()
{
    try{
    vk_albums * Albums = new vk_albums();                            //Объект класса "Получение списка альбомов"
    connect(this, SIGNAL(complete_Download_Albums()), Albums, SLOT(deleteLater()));
    connect(Albums, SIGNAL(albums_parse(QList< QPair<QString, QString> >)), //Получение списка альбомов
           this, SLOT(print_albums(QList<QPair<QString,QString> >)));
    Albums->get_albums(UsId, Token);                          //Отправка запроса на получение списка альбомов
    }
    catch(QException)
    {

    }
}

void Widget::get_Start_Playlist()
{
    this->Myplaylist();                                        //Загрузка стартового плейлиста (мои аудиозаписи)
    flag_if_MyPlaylist_isPlaying = true;
    flag_if_RecomendationPlaylist = false;
    row = 0; //Установка начальной строки в виджете-плейлисте
}

void Widget::post_User_trackVisitor()
{
    try{
    VkGet *get = new VkGet;
    QUrl current("https://api.vk.com/method/stats.trackVisitor");
    QUrlQuery reqParams;
    reqParams.addQueryItem("access_token", Token);
    current.setQuery(reqParams);
    get->GET(current);
    }
    catch(QException)
    {

    }
}

//Проверка на горячие клавиши
bool Widget::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    { // Была нажата одна из горячих клавиш

        if (msg->wParam == 0)                                         //Play / Pause
        {
            QMediaPlayer::State state = player->state();
            switch(state){

            case QMediaPlayer::PlayingState:
                player->pause();
                break;

            case QMediaPlayer::PausedState:
                player->play();
                break;


            case QMediaPlayer::StoppedState:
                PlayMusic = "Home";
                int RowDoubleClick = 0;
                emit PlaySong(PlayMusic, RowDoubleClick);
                break;
            }
            return true;
        }
        if (msg->wParam == 1)
        {
            PlayMusic = "Next";                                  //СЛЕДУЮЩАЯ ПЕСНЯ
            int RowDoubleClick = 0;
            emit PlaylingSong(PlayMusic, RowDoubleClick);
            return true;
        }
        if (msg->wParam == 2)                                     //Предыдущая песня
        {
            PlayMusic = "Previous";
            int RowDoubleClick = 0;
            emit PlaylingSong(PlayMusic, RowDoubleClick);
            return true;
        }
        if (msg->wParam == 3)
        {
            if(!flag_if_MyPlaylist_isPlaying){
                vk_add * add = new vk_add;
                add->add_song(Id_song, Owner_Id_song, Token);
                return true;
            }
        }
        if (msg->wParam == 4)
        {
            ui->DownloadButton->clicked();
            return true;
        }
    }

    return false;
}

//Вывод друзей в выпадающий список
void Widget::print_friend(QList<QPair<QString, QString> > users)
{
   try
    {
        for(int i = 0; i < users.size(); i++){
            ui->List_2->addItem(users.at(i).first);
            ui->List->addItem(users.at(i).first);
            friend_ids[users.at(i).first] = users.at(i).second;
        }

        emit complete_Download_Friend();
    }
    catch(QException)
    {

    }
    this->get_User_Group();
}

//Вывод групп в выпадающий список
void Widget::print_group(QList< QPair<QString, QString> > groups)
{
    try
    {
        for(int i = 0; i < groups.size(); i++){
            ui->GroupList->addItem(groups.at(i).first);
            ui->List_3->addItem(groups.at(i).first);
            group_ids[groups.at(i).first] = groups.at(i).second;
        }

        emit complete_Download_Group();
    }
    catch(QException)
    {

    }
    this->get_User_Albums();
}

void Widget::print_albums(QList<QPair<QString, QString> > albums)
{
   try
    {
        for(int i = 0; i < albums.size(); i++){
            ui->List_Albums->addItem(albums.at(i).first);
            albums_ids[albums.at(i).first] = albums.at(i).second;
        }

        emit complete_Download_Albums();
    }
    catch(QException)
    {

    }
    this->get_Start_Playlist();
}

//задать текст для строки поиска
void Widget::print_Default_Search_Line()
{
    ui->Search_Line->setText(" Поиск музыки");
}

//Вывод предупреждений
void Widget::print_Warning(QString str)
{
    Messages *messages = new Messages;
    QString title, text;

    title = "Предупреждение";
    text = "Попробуйте перезапустить программу...";
    messages->set_Title_and_Text(title, text, false, false);
    messages->show();
}

//Выбор аудиозаписей друга
void Widget::Friends_music(QString tmp)
{
    ui->PhotoGroup->hide();

    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->setEnabled(false);
    NameFRIEND = tmp;
    int flag = 1;
    temp_frId = friend_ids.value(tmp);
    QUrl current("https://api.vk.com/method/audio.get");
    this->changedPlaylist(current, flag, 1, " ");
    flag_if_MyPlaylist_isPlaying = false;
    flag_if_RecomendationPlaylist = false;
}

//Выбор аудиозаписей группы
void Widget::Groups_music(QString tmp)
{
    ui->PhotoFriend->hide();

    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->setEnabled(false);
    NameGROUP = tmp;
    int flag = 1;
    temp_grId = group_ids.value(tmp);
    QUrl current("https://api.vk.com/method/audio.get");
    this->changedPlaylist(current, flag, 2, " ");
    flag_if_MyPlaylist_isPlaying = false;
    flag_if_RecomendationPlaylist = false;
}

//Изменение иконки громкости
void Widget::print_volume_icon(int value_volume)
{
    if(player->isMuted() == false)
    {
        if(value_volume == 0)
        {
             ui->MuteButton->setStyleSheet("border-image: url(:/new/prefix1/icons/not_should.gif) stretch;");
        }
        if(value_volume <= 70 && value_volume >= 30)
        {
             ui->MuteButton->setStyleSheet("border-image: url(:/new/prefix1/icons/should2.gif) stretch;");
        }
        if(value_volume < 30 && value_volume > 0)
        {
             ui->MuteButton->setStyleSheet("border-image: url(:/new/prefix1/icons/should1.gif) stretch;");
        }
        if(value_volume >70)
        {
             ui->MuteButton->setStyleSheet("border-image: url(:/new/prefix1/icons/should3.gif) stretch;");
        }
    }
}

//Нажатие на слайдер песни
void Widget::position()
{
    disconnect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionREVERS(qint64)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(positionTWO(int)));
}

//Перемещение по времени песни (в плеере)
void Widget::positionTWO(int value)
{
    qint64 VAL = value;
    player->setPosition(VAL);
}

//Перемещение по времени песни (на слайдере)
void Widget::positionREVERS(qint64 value)
{
    int VAL = value;
    ui->horizontalSlider->setValue(VAL);
}

//Отжатие слайдера песни
void Widget::positionTHREE()
{
    disconnect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(positionTWO(int)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionREVERS(qint64)));
}

//Выбор композиций в зависимости от состояния
void Widget::PlaylingSong(QString flag, int RowDoubleClick)
{
    int tmpRow;
    int tmpSwitch;

    if(flag == "Home")
        tmpSwitch = 1;
    if(flag == "Next")
        tmpSwitch = 2;
    if(flag == "Previous")
        tmpSwitch = 3;
    if(flag == "DoubleClick")
        tmpSwitch = 4;

    switch (tmpSwitch){

    case 1:
        if(sequence == "Random")
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            tmpRow = qrand() % (ui->tableWidget->rowCount()-2);
            if(tmpRow == 0 && offset != 0)
                tmpRow = 1;

            this->ProcessingSong(tmpRow);
            break;
        }
        if(sequence == "Repeat")
        {
            tmpRow = row;
            this->ProcessingSong(tmpRow);
            break;
        }
        if(offset != 0)
            tmpRow = 1;
        else
            tmpRow = 0;
        this->ProcessingSong(tmpRow);
        break;

    case 2:
        if(sequence == "Random")
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            tmpRow = qrand() % (ui->tableWidget->rowCount()-2);
            if(tmpRow == 0 && offset != 0)
                tmpRow = 1;

            this->ProcessingSong(tmpRow);
            break;
        }
        if(sequence == "Repeat")
        {
            tmpRow = row;
            this->ProcessingSong(tmpRow);
            break;
        }
        if(ui->tableWidget->rowCount() == row+2){
            if(offset != 0)
                tmpRow = 1;
            else
                tmpRow = 0;
        }
        else
            tmpRow = row + 1;
        this->ProcessingSong(tmpRow);
        break;

    case 3:
        if(sequence == "Random")
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            tmpRow = qrand() % (ui->tableWidget->rowCount()-2);
            if(tmpRow == 0 && offset != 0)
                tmpRow = 1;

            this->ProcessingSong(tmpRow);
            break;
        }
        if(sequence == "Repeat")
        {
            tmpRow = row;
            this->ProcessingSong(tmpRow);
            break;
        }

        if(offset !=0 && row == 1)
            tmpRow = ui->tableWidget->rowCount()-2;
        else if(offset ==0 && row == 0)
            tmpRow = ui->tableWidget->rowCount()-2;
        else
            tmpRow = row - 1;

        this->ProcessingSong(tmpRow);
        break;

    case 4:
        this->ProcessingSong(RowDoubleClick);
        break;
    }
}

//Обработка текущей композиции
void Widget::ProcessingSong(int tmpRow)
{
    try
    {
        if(tmpArtist_Title.count() != 0){

        QTableWidgetItem* Artist = new QTableWidgetItem();
        QTableWidgetItem* Title = new QTableWidgetItem();
        QTableWidgetItem* Duration = new QTableWidgetItem();
        QTableWidgetItem* Genre = new QTableWidgetItem();
        QTableWidgetItem* id_song = new QTableWidgetItem();
        QTableWidgetItem* owner_id = new QTableWidgetItem();
        QTableWidgetItem* lyrics_id = new QTableWidgetItem();
        QTableWidgetItem* url_song = new QTableWidgetItem();

        Artist = ui->tableWidget->item(tmpRow, 0);
        Title = ui->tableWidget->item(tmpRow, 1);
        Duration = ui->tableWidget->item(tmpRow, 2);
        Genre = ui->tableWidget->item(tmpRow, 3);
        id_song = ui->tableWidget->item(tmpRow, 4);
        owner_id = ui->tableWidget->item(tmpRow, 5);
        lyrics_id = ui->tableWidget->item(tmpRow, 6);
        url_song = ui->tableWidget->item(tmpRow, 7);

        Artist_song = Artist->text();
        Title_song = Title->text();
        Duration_song = Duration->text();
        Genre_song = Genre->text();
        Id_song = id_song->text();
        Owner_Id_song = owner_id->text();
        Lyrics_Id_song = lyrics_id->text();
        Url_song = url_song->text();

              QTableWidgetItem* itemtmp = new QTableWidgetItem();
              itemtmp = ui->tableWidget->item(row, 0);
              ui->tableWidget->setItemSelected(itemtmp,false);
              itemtmp->setIcon(QIcon());
              itemtmp = ui->tableWidget->item(row, 1);
              ui->tableWidget->setItemSelected(itemtmp,false);
              itemtmp = ui->tableWidget->item(row, 2);
              ui->tableWidget->setItemSelected(itemtmp,false);
              itemtmp = ui->tableWidget->item(row, 3);
              ui->tableWidget->setItemSelected(itemtmp,false);
              row = Artist->row();
              Artist->setIcon(QIcon(":/new/prefix1/icons/play.gif"));
              ui->tableWidget->setCurrentItem(Artist);
              ui->tableWidget->setItemSelected(Artist,true);
              ui->tableWidget->setItemSelected(Title,true);
              ui->tableWidget->setItemSelected(Duration,true);
              ui->tableWidget->setItemSelected(Genre,true);

              textsong->setString(" ");


             player->setMedia(QMediaContent(QUrl(Url_song)));

             player->play();

              if(status_enable == 1 && ui->post_Status->isEnabled() == true)
                this->install_status();

        }
    }
    catch(QException)
    {

    }
}

//Вывод плэйлиста в главном окне
void Widget::print_audioTable(QList< QPair<QString, QString> > Artist_Title, QList<QPair<QString, QString> > Id_Url, QList< QPair<QString, QString> > Duration_Genre, QList< QPair<QString, QString> > OwnerId_lyricsId)
{
    try
    {
        Loading.hide();
        disconnect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayMenu(QPoint)));
        ui->tableWidget->verticalScrollBar()->setValue(0);

        ui->tableWidget->removeCellWidget(ui->tableWidget->rowCount()-1,1);
        ui->tableWidget->removeCellWidget(0,1);
        ui->tableWidget->clear();                                       //Очистка виджета-плэйлиста

        int rowC = 0;
        int flag_found_song = 0;
        QString tempTitle,tempArtist, tempDuration, tempGenre, tempIdSond, tempOwnerId, tempLyricsId, tempUrlSong;
        QTableWidgetItem* Column0 = new QTableWidgetItem();             //Создание Колонки "Артист"
        QTableWidgetItem* Column1 = new QTableWidgetItem();             //Создание колонки "Название песни"
        QTableWidgetItem* Column2 = new QTableWidgetItem();             //Создание Колонки "Длина песни"
        QTableWidgetItem* Column3 = new QTableWidgetItem();             //Создание колонки "Жанр"
        QTableWidgetItem* Column4 = new QTableWidgetItem();             //Создание колонки "id песни"
        QTableWidgetItem* Column5 = new QTableWidgetItem();             //Создание колонки "owner_id"
        QTableWidgetItem* Column6 = new QTableWidgetItem();             //Создание колонки "lyrics_id"
        QTableWidgetItem* Column7 = new QTableWidgetItem();             //Создание колонки "url_Song"

        QFont font;
        font.setPointSize(8);
        Column0->setFont(font);
        Column1->setFont(font);
        Column2->setFont(font);
        Column3->setFont(font);
        Column0->setText("Исполнитель");
        Column1->setText("Название");
        Column2->setText("Длина");
        Column3->setText("Жанр");
        Column4->setText("id");
        Column5->setText("owner_id");
        Column6->setText("lyrics_id");
        Column6->setText("url_Song");

        ui->tableWidget->setHorizontalHeaderItem(0, Column0);           //Добавление на виджет колонки 1 Исполнитель
        ui->tableWidget->setHorizontalHeaderItem(1, Column1);           //Добавление на виджет колонки 2 Название
        ui->tableWidget->setHorizontalHeaderItem(2, Column2);           //Добавление на виджет колонки 3 Длина
        ui->tableWidget->setHorizontalHeaderItem(3, Column3);           //Добавление на виджет колонки 4 Жанр
        ui->tableWidget->setHorizontalHeaderItem(4, Column4);           //Добавление на виджет колонки 5 id песни
        ui->tableWidget->setHorizontalHeaderItem(5, Column5);           //Добавление на виджет колонки 6 owner_id
        ui->tableWidget->setHorizontalHeaderItem(6, Column6);           //Добавление на виджет колонки 7 lyrics_id
        ui->tableWidget->setHorizontalHeaderItem(7, Column7);           //Добавление на виджет колонки 7 url_Song

        ui->tableWidget->verticalHeader()->setDefaultSectionSize(20);   //Задание размера по вертикали
        //ui->tableWidget->horizontalHeader()->setDefaultSectionSize(140);//Задание размера по горизонтали


        if(offset == 0){
            rowC = 0;
            ui->tableWidget->setRowCount(Artist_Title.count()+1);                    //Задание колличества строк в таблице
        }
        else{
            rowC = 1;
            ui->tableWidget->setRowCount(Artist_Title.count()+2);
        }

        ui->tableWidget->setColumnWidth(0,84);      //Размеры колонок
        ui->tableWidget->setColumnWidth(1,120);     //Размеры колонок
        ui->tableWidget->setColumnWidth(2,50);      //Размеры колонок
        ui->tableWidget->setColumnWidth(3,60);      //Размеры колонок
        ui->tableWidget->setColumnWidth(4,0);       //Размеры колонок
        ui->tableWidget->setColumnWidth(5,0);       //Размеры колонок
        ui->tableWidget->setColumnWidth(6,0);       //Размеры колонок
        ui->tableWidget->setColumnWidth(7,0);       //Размеры колонок

        /*///////////// ЗАПОЛЕНИЕ СТРОК В ТАБЛИЦЕ //////////////*/
        for (int i = 0; i < Artist_Title.size(); ++i) {
            QTableWidgetItem* Artist = new QTableWidgetItem();
            QTableWidgetItem* Title = new QTableWidgetItem();
            QTableWidgetItem* Duration = new QTableWidgetItem();
            QTableWidgetItem* Genre = new QTableWidgetItem();
            QTableWidgetItem* id_song = new QTableWidgetItem();
            QTableWidgetItem* owner_id = new QTableWidgetItem();
            QTableWidgetItem* lyrics_id = new QTableWidgetItem();
            QTableWidgetItem* url_song = new QTableWidgetItem();

            tempArtist = Artist_Title.at(i).first;
            tempTitle = Artist_Title.at(i).second;
            tempDuration = Duration_Genre.at(i).first;
            tempGenre = Duration_Genre.at(i).second;
            tempIdSond = Id_Url.at(i).first;
            tempOwnerId = OwnerId_lyricsId.at(i).first;
            tempLyricsId = OwnerId_lyricsId.at(i).second;
            tempUrlSong = Id_Url.at(i).second;


            if(!tempTitle.isEmpty() && !tempArtist.isEmpty())
            {
                Artist->setText(tempArtist);
                Title->setText(tempTitle);
                Duration->setText(tempDuration);
                Genre->setText(tempGenre);
                id_song->setText(tempIdSond);
                owner_id->setText(tempOwnerId);
                lyrics_id->setText(tempLyricsId);
                url_song->setText(tempUrlSong);

                ui->tableWidget->setItem(rowC, 0, Artist);
                ui->tableWidget->setItem(rowC, 1, Title);
                ui->tableWidget->setItem(rowC, 2, Duration);
                ui->tableWidget->item(rowC, 2)->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(rowC, 3, Genre);
                ui->tableWidget->setItem(rowC, 4, id_song);
                ui->tableWidget->setItem(rowC, 5, owner_id);
                ui->tableWidget->setItem(rowC, 6, lyrics_id);
                ui->tableWidget->setItem(rowC, 7, url_song);


                if(tempIdSond == Id_song && tempOwnerId == Owner_Id_song){
                    flag_found_song = 1;
                    row = rowC;
                }

                rowC++;
            }
        }
        if(flag_found_song == 1)
            this->mark_Song();
        else
            row = 0;

        flag_found_song = 0;

            if(offset != 0){
                QPushButton *previous_300 = new QPushButton("Предыдущие");
                connect(previous_300, SIGNAL(clicked()), this, SLOT(click_previous_300()));
                ui->tableWidget->setCellWidget(0, 1, previous_300);
                row = 1;
            }
            if(Artist_Title.count() != 0){
                QPushButton *next_300 = new QPushButton("Следующие");
                connect(next_300, SIGNAL(clicked()), this, SLOT(click_next_300()));
                ui->tableWidget->setCellWidget(rowC, 1, next_300);
            }
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error Loading Playlist");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }

    /*///////////////////////////////////////////////////////*/
    tmpArtist_Title = Artist_Title;
    ui->tabplaylist->setEnabled(true);                               //Включить переключение плэйлистов
    ui->Search_Line->setEnabled(true);                               //Включить строку поиска
    ui->Genre_Button->setEnabled(true);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayMenu(QPoint)));

    ui->List->setEnabled(true);
    ui->GroupList->setEnabled(true);

}

//Вывод длительности песни и её названия
void Widget::print_duration(qint64 ab)
{
    if(ab!=0)
    {                    
        /*//////////// ПОДСЧЕТ ВРЕМЕНИ ПЕСНИ И ВЫВОД ////////////*/
        qint64 a = ab, min, sec;
        a = a/1000;
        min=a/60;
        sec=a%60;
        if(sec < 10)
        {
             Duration_song_Player = QString("%1:0%2").arg(min).arg(sec);
        }
        else
        {
            Duration_song_Player = QString("%1:%2").arg(min).arg(sec);    //Запись в стринг мин. и сек. песни
        }
        ui->duration->setText(Duration_song_Player);                      //Вывести время песни
        /*////////////////////////////////////////////////////////*/

        ui->DownloadButton->setStyleSheet("border-image: url(:/new/prefix1/icons/save.gif) stretch;");
        ui->horizontalSlider->setMaximum(ab);                       //Установить длину слайдера песни (по времени песни)

        if(!Lyrics_Id_song.isEmpty())
        {
            textsong->setGeometry(QRect(32, 487, 285, 22));
            ui->Lyrics_BTN->show();            
        }
        else
        {
            ui->Lyrics_BTN->hide();
            textsong->setGeometry(QRect(32, 487, 307, 22));
        }

        QString tmpNameSong = Artist_song + "_" + Title_song;

        textsong->setString(tmpNameSong + "                                                         ");   //Вывести название песни в строку в плеере

        osd->SetMessage(Artist_song,Title_song,QImage(":/new/prefix1/vk.ico"));
        if(show_Notif)
            osd->show();
    }
}

//Таймер песни
void Widget::print_time_song(qint64 ab)
{
    QString tmp;
    qint64 a = ab, min, sec;
    a = a/1000;
    min=a/60;
    sec=a%60;

    if(sec < 10)
    {
         tmp = QString("%1:0%2").arg(min).arg(sec);
    }
    else
    {
        tmp = QString("%1:%2").arg(min).arg(sec); //Запись в стринг мин. и сек. песни
    }
    ui->duration->setText(tmp + "/" + Duration_song_Player);
}

//Установка прозрачности окна плеера
void Widget::transparency(int value)
{
    tran = value;
    tran = tran/100;
    this->setWindowOpacity(tran);
}

//Двойное нажатие на песни в плэйлисте
void Widget::selectedItem(QTableWidgetItem *item)
{
    int RowDoubleClick = item->row();
    PlayMusic = "DoubleClick";
    emit PlaylingSong(PlayMusic, RowDoubleClick);
    trIcon->setIcon(QIcon(QPixmap(":/new/prefix1/icons/pause.gif")));
}

//Создание вкладки друга и загрузка его аватарки
void Widget::print_nameFriend_andPhoto(QPair<QString, QString> NamePhoto)
{
    try
    {
        if(create_tab){


        VkGet *get = new VkGet;
        QByteArray temp = get->GET(NamePhoto.second);
        delete get;
        QImage px;
        px.loadFromData(temp);


        QFile *file = new QFile("avatarfriend.jpg");

                if(file->open(QFile::ReadWrite))
                {
                    px.save(file,"jpg");
                    file->close();
                }

            ui->PhotoFriend->setStyleSheet(
                "QPushButton  {"
                "border-image: url(avatarfriend.jpg);"
                "border-radius: 8px;"
                "}"
                "QPushButton:pressed  {"
                    "background-color: rgb(36, 116, 160);"
                "}"
                );

           ui->PhotoGroup->hide();
           if(!temp.isEmpty())
               ui->PhotoFriend->show();
            temp.clear();

        QWidget *newTab = new QWidget(ui->tabplaylist);

        QStringList lst = QString(NameFRIEND).replace(QRegExp("( )"), ",\\1")
                                         .split(",", QString::SkipEmptyParts);

        QString NameShort = lst.at(0)[1];
        NameShort = NameShort + ".";

        if(NameFRIEND.size() > 15)
        {
            ui->tabplaylist->addTab(newTab, NameShort + lst.at(1).mid(0,12));
        }
        else
            ui->tabplaylist->addTab(newTab, NameFRIEND);

        ui->tabplaylist->setCurrentIndex(3);


        disconnect(ui->List, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного друга
                this, SLOT(Friends_music(QString)));
        ui->List->setCurrentIndex(0);
        connect(ui->List, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного друга
                this, SLOT(Friends_music(QString)));
        }
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Get photo friend");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }

}

//Создание вкладки группы и загрузка её аватарки
void Widget::print_nameGroup_andPhoto(QString Id_Group)
{
    try
    {
        if(create_tab){


        VkGet *get = new VkGet;

        QUrl current("https://api.vk.com/method/groups.getById");
        QUrlQuery reqParams;
        reqParams.addQueryItem("group_ids", Id_Group);
        current.setQuery(reqParams);
        QByteArray Tmp = get->GET(current);
        QVariantList List = parse(Tmp).toMap().value("response").toList();
        QString photo;
        for(int i = 0; i < List.size(); i++)
        {
                QVariantMap current = List[i].toMap();
                photo = current.value("photo").toString();
        }

        QByteArray temp = get->GET(photo);
        get->deleteLater();
        QImage px;
        px.loadFromData(temp);
        temp.clear();

        QFile *file = new QFile("avatargroup.jpg");

                if(file->open(QFile::ReadWrite))
                {
                    px.save(file,"jpg");
                    file->close();
                }

            ui->PhotoGroup->setStyleSheet(
                "QPushButton  {"
                "border-image: url(avatargroup.jpg);"
                "border-radius: 8px;"
                "}"
                "QPushButton:pressed  {"
                    "background-color: rgb(36, 116, 160);"
                "}"
                );
        ui->PhotoFriend->hide();
        ui->PhotoGroup->show();

        QWidget *newTab = new QWidget(ui->tabplaylist);


        if(NameGROUP.size() > 19)
        {
            ui->tabplaylist->addTab(newTab, NameGROUP.mid(0,13)+"...");
        }
        else
            ui->tabplaylist->addTab(newTab, NameGROUP);

        ui->tabplaylist->setCurrentIndex(3);


        disconnect(ui->GroupList, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранной группы
                this, SLOT(Groups_music(QString)));
        ui->GroupList->setCurrentIndex(0);
        connect(ui->GroupList, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранной группы
                this, SLOT(Groups_music(QString)));
        }
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Get photo group");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }

}

void Widget::print_newAlbumTab()
{
    try
    {
        if(create_tab){

           ui->PhotoGroup->hide();
           ui->PhotoFriend->hide();

        QWidget *newTab = new QWidget(ui->tabplaylist);

        QStringList lst = QString(NameAlbum).replace(QRegExp("( )"), ",\\1")
                                         .split(",", QString::SkipEmptyParts);

        QString NameShort = lst.at(0)[1];
        NameShort = NameShort + ".";

        if(NameAlbum.size() > 15)
        {
            ui->tabplaylist->addTab(newTab, NameShort + lst.at(1).mid(0,12));
        }
        else
            ui->tabplaylist->addTab(newTab, NameAlbum);

        disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
                 this, SLOT(changePlaylist(int)));
        ui->tabplaylist->setCurrentIndex(3);
        connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
                 this, SLOT(changePlaylist(int)));
        }
    }
    catch(QException)
    {

    }
}

//Вывод моей аватарки
void Widget::print_MyPhoto(QString photo)
{
    try
    {
        VkGet *get = new VkGet;
        QByteArray temp = get->GET(photo);
        get->deleteLater();
        QImage px;
        px.loadFromData(temp);
        temp.clear();

        QFile *file = new QFile("myavatar.jpg");

                if(file->open(QFile::ReadWrite))
                {
                    px.save(file,"jpg");
                    file->close();
                }

            ui->Photo->setStyleSheet(
                "QPushButton  {"
                "border-image: url(myavatar.jpg);"
                "border-radius: 8px;"
                "}"
                "QPushButton:pressed  {"
                    "background-color: rgb(36, 116, 160);"
                "}"
                );
            ui->Photo->show();
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error get photo");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }

        this->complete_Download_My_Photo();

        this->get_User_Friend();
}

//Контекстное меню Плэйлиста
void Widget::displayMenu(const QPoint &pos)
{
    if(!tmpArtist_Title.isEmpty() && ui->tableWidget->itemAt(pos) != NULL){
        add_Audio_Id = ui->tableWidget->item(ui->tableWidget->itemAt(pos)->row(),4)->text();
        add_Owner_Id = ui->tableWidget->item(ui->tableWidget->itemAt(pos)->row(),5)->text();
        tmpTitle = ui->tableWidget->item(ui->tableWidget->itemAt(pos)->row(),1)->text();
        tmpArtist = ui->tableWidget->item(ui->tableWidget->itemAt(pos)->row(),0)->text();
        tmpUrl = ui->tableWidget->item(ui->tableWidget->itemAt(pos)->row(),7)->text();
        tmpGenre = ui->tableWidget->item(ui->tableWidget->itemAt(pos)->row(),3)->text();

        QMenu *menu = new QMenu("VKPlayer");

        menu->setStyleSheet(
                    "QMenu {"
                    "background-color: rgb(45, 45, 45);"
                    "border-radius: 9px;"
                    "border: 1px solid black;"
                    "color: white;"

                "}"
                "QMenu::item:selected {"
                    "background: rgb(80, 80, 80);"
                "}"
                    );

        QAction *Remove = new QAction(QIcon(":/new/prefix1/icons/remove.png"), "Удалить", menu);
        QAction *Add = new QAction(QIcon(":/new/prefix1/icons/add.png"), "Добавить", menu);
        QAction *Download = new QAction(QIcon(":/new/prefix1/icons/save.png"), "Загрузить", menu);
        QAction *send_to_my_wall = new QAction(QIcon(":/new/prefix1/icons/wall.png"), "Отправить себе на стену", menu);
        QAction *send_to_friend_wall = new QAction(QIcon(":/new/prefix1/icons/wall.png"), "Отправить на стену другу", menu);
        QAction *send_message_with_audio = new QAction(QIcon(":/new/prefix1/icons/message.png"), "Отправить сообщением", menu);
        QAction *send_to_group_wall = new QAction(QIcon(":/new/prefix1/icons/wall.png"), "Отправить на стену группы", menu);
        QAction *Edit = new QAction(QIcon(":/new/prefix1/icons/text1.png"), "Редактировать", menu);

            if(flag_if_MyPlaylist_isPlaying){
                menu->addAction(Remove);
                menu->addAction(Edit);
            }
            else
                menu->addAction(Add);

            if(flag_if_RecomendationPlaylist){
                menu->addAction(Remove);
            }

            menu->addAction(Download);
            menu->addAction(send_to_my_wall);
            menu->addAction(send_to_friend_wall);
            menu->addAction(send_to_group_wall);
            menu->addAction(send_message_with_audio);

            QAction *Val = menu->exec(ui->tableWidget->viewport()->mapToGlobal(pos));
            if (Val == Add)
            {
                vk_add * add = new vk_add;
                add->add_song(add_Audio_Id, add_Owner_Id, Token);
                delete menu;
            }
            if (Val == Remove)
            {
                if(!flag_if_RecomendationPlaylist){
                    vk_add * add = new vk_add;
                    add->remove_song(add_Audio_Id, add_Owner_Id, Token);
                }
                ui->tableWidget->removeRow(ui->tableWidget->itemAt(pos)->row());
                delete menu;
            }
            if (Val == Edit)
            {
                tmprow = ui->tableWidget->itemAt(pos)->row();
                AudioEdit * audioedit = new AudioEdit();
                connect(audioedit, SIGNAL(success_edit(QString,QString,QString)),
                        this, SLOT(print_edit_song(QString,QString,QString)));
                connect(this, SIGNAL(complete_Editing()), audioedit, SLOT(deleteLater()));

                audioedit->recieve_data(add_Audio_Id, add_Owner_Id, tmpArtist, tmpTitle, tmpGenre, Token);
                audioedit->show();
                delete menu;
            }
            if (Val == Download)
            {
                this->Download_fuction(2, tmpArtist, tmpTitle, tmpUrl );
                delete menu;
            }
            if(Val == send_to_my_wall)
            {
                vk_send_attachment * attachment = new vk_send_attachment();
                attachment->process_attachment(add_Audio_Id, add_Owner_Id, UsId, Token, 0);
                delete menu;
            }
            if(Val == send_to_friend_wall)
            {
                attachment_wall_or_message = 0;
                ui->List_2->showPopup();
                delete menu;
            }
            if(Val == send_to_group_wall)
            {
                attachment_wall_or_message = 3;
                ui->List_3->showPopup();
                delete menu;
            }
            if(Val == send_message_with_audio)
            {
                attachment_wall_or_message = 1;
                ui->List_2->showPopup();
                delete menu;
            }

    }
}

//Изменение данных песни после редактирования
void Widget::print_edit_song(QString artist, QString title, QString genre)
{
    ui->tableWidget->item(tmprow, 0)->setText(artist);
    ui->tableWidget->item(tmprow, 1)->setText(title);
    ui->tableWidget->item(tmprow, 3)->setText(genre);

    emit complete_Editing();
}

//Заполнение жанрами выпадающий список
void Widget::print_popular_genre()
{
    QPair<QString, QString> popgen;
    popgen.first = "Default";
    popgen.second = "";
    popular_genre.push_back(popgen);
    popgen.first = "Rock";
    popgen.second = "1";
    popular_genre.push_back(popgen);
    popgen.first = "Pop";
    popgen.second = "2";
    popular_genre.push_back(popgen);
    popgen.first = "Rap & Hip-Hop";
    popgen.second = "3";
    popular_genre.push_back(popgen);
    popgen.first = "Easy Listening";
    popgen.second = "4";
    popular_genre.push_back(popgen);
    popgen.first = "Dance & House";
    popgen.second = "5";
    popular_genre.push_back(popgen);
    popgen.first = "Instrumental";
    popgen.second = "6";
    popular_genre.push_back(popgen);
    popgen.first = "Metal";
    popgen.second = "7";
    popular_genre.push_back(popgen);
    popgen.first = "Alternative";
    popgen.second = "21";
    popular_genre.push_back(popgen);
    popgen.first = "Dubstep";
    popgen.second = "8";
    popular_genre.push_back(popgen);
    popgen.first = "Jazz & Blues";
    popgen.second = "9";
    popular_genre.push_back(popgen);
    popgen.first = "Drum & Bass";
    popgen.second = "10";
    popular_genre.push_back(popgen);
    popgen.first = "Trance";
    popgen.second = "11";
    popular_genre.push_back(popgen);
    popgen.first = "Chanson";
    popgen.second = "12";
    popular_genre.push_back(popgen);
    popgen.first = "Ethnic";
    popgen.second = "13";
    popular_genre.push_back(popgen);
    popgen.first = "Acoustic & Vocal";
    popgen.second = "14";
    popular_genre.push_back(popgen);
    popgen.first = "Reggae";
    popgen.second = "15";
    popular_genre.push_back(popgen);
    popgen.first = "Classical";
    popgen.second = "16";
    popular_genre.push_back(popgen);
    popgen.first = "Indie Pop";
    popgen.second = "17";
    popular_genre.push_back(popgen);
    popgen.first = "Speech";
    popgen.second = "19";
    popular_genre.push_back(popgen);
    popgen.first = "Electropop & Disco";
    popgen.second = "22";
    popular_genre.push_back(popgen);
    popgen.first = "Other";
    popgen.second = "18";
    popular_genre.push_back(popgen);

    for(int i = 0; i < popular_genre.size(); i++){
       ui->List_4->addItem(popular_genre.at(i).first);
    }
}

//Обработка после выбора жанра популярной музыки
void Widget::process_pop_genre(QString genre)
{
    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    disconnect(ui->List_4, SIGNAL(currentTextChanged(QString)),
            this, SLOT(process_pop_genre(QString)));

    ui->tabplaylist->setCurrentIndex(0);
    ui->List_4->setCurrentIndex(0);

    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    connect(ui->List_4, SIGNAL(currentTextChanged(QString)),
            this, SLOT(process_pop_genre(QString)));

    QString type_genre;
    for(int i = 0; i < popular_genre.size() ; ++i){
        if(genre == popular_genre.at(i).first){
            type_genre = popular_genre.at(i).second;
            break;
        }
    }

    ui->PhotoFriend->hide();
    ui->PhotoGroup->hide();

    ui->tabplaylist->setEnabled(false);
    flag_if_MyPlaylist_isPlaying = false;
    flag_if_RecomendationPlaylist = false;

    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));

    int flag = 0;
    QUrl current("https://api.vk.com/method/audio.getPopular");
    this->changedPlaylist(current, flag, 0, type_genre);

}

void Widget::selected_album(QString album)
{
    disconnect(ui->List_Albums, SIGNAL(currentTextChanged(QString)),
            this, SLOT(selected_album(QString)));

    ui->List_Albums->setCurrentIndex(0);

    connect(ui->List_Albums, SIGNAL(currentTextChanged(QString)),
            this, SLOT(selected_album(QString)));

    ui->PhotoFriend->hide();
    ui->PhotoGroup->hide();

    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->setEnabled(false);
    NameAlbum = album;

    temp_albumId = albums_ids.value(album);

    int flag = 3;
    QUrl current("https://api.vk.com/method/audio.get");
    this->changedPlaylist(current, flag, 0, " ");
}

//Вывод ошибок плеера
void Widget::print_Error_Player(QMediaPlayer::Error error)
{
    Messages * messages = new Messages;
    QString title, text;
    title = "Ошибка";

    switch(error){

    case QMediaPlayer::ResourceError:
        player->stop();
        text = "A media resource couldn't be resolved.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QMediaPlayer::FormatError:
        player->stop();
        text = "The format of a media resource isn't (fully) supported. Playback may still be possible, but without an audio or video component.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QMediaPlayer::NetworkError:
        player->stop();
        text = "A network error occurred.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QMediaPlayer::AccessDeniedError:
        player->stop();
        text = "There are not the appropriate permissions to play a media resource.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QMediaPlayer::ServiceMissingError:
        player->stop();
        text = "A valid playback service was not found, playback cannot proceed.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    default:
        player->stop();
        text = "Invalid Error";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;
    }

}

//Изменение иконки Плей в зависимости от состояния плеера
void Widget::print_Image_Player_State(QMediaPlayer::State state)
{
    switch(state){

    case QMediaPlayer::PlayingState:
        ui->PlayButton->setStyleSheet("border-image: url(:/new/prefix1/icons/pause.gif) stretch;");
        trIcon->setIcon(QIcon(QPixmap(":/new/prefix1/icons/pause.gif")));
        osd->SetMessage("Сейчас играет",Artist_song + " - " + Title_song,QImage(":/new/prefix1/vk.ico"));
        if(show_Notif)
            osd->show();
        break;

    case QMediaPlayer::PausedState:
        ui->PlayButton->setStyleSheet("border-image: url(:/new/prefix1/icons/play.gif) stretch;");
        trIcon->setIcon(QIcon(QPixmap(":/new/prefix1/icons/play.gif")));
        osd->SetMessage("VKPlayer", "Приостановлено", QImage(":/new/prefix1/vk.ico"));
        if(show_Notif)
            osd->show();
        break;


    case QMediaPlayer::StoppedState:
        ui->PlayButton->setStyleSheet("border-image: url(:/new/prefix1/icons/play.gif) stretch;");
        trIcon->setIcon(QIcon(QPixmap(":/new/prefix1/icons/play.gif")));
        osd->SetMessage("VKPlayer", "Остановлено", QImage(":/new/prefix1/vk.ico"));
        if(show_Notif)
            osd->show();
        textsong->setString(" ");
        break;
    }
}

//Доступность аудио
void Widget::AudioAvailable(bool val)
{
    qDebug()<<"AudioAvilable "<<val;
}

void Widget::audioBuffer(QAudioBuffer buffer)
{
    /*ui->SpectrumLeft->setMaximum(buffer.frameCount());
    ui->SpectrumRight->setMaximum(buffer.frameCount());
    ui->SpectrumLeft->setValue(buffer.data<QAudioBuffer::S16U>()->left);
    ui->SpectrumRight->setValue(buffer.data<QAudioBuffer::S16U>()->right);
    buffer.~QAudioBuffer();*/
}

//Запрос на отправку песни на стену или сообщением
void Widget::post_attachment(QString FrName)
{
    disconnect(ui->List_2, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного друга (для attachment)
            this, SLOT(post_attachment(QString)));
    disconnect(ui->List_3, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранной группы (для attachment)
            this, SLOT(post_attachment(QString)));

    ui->List_2->setCurrentIndex(0);
    ui->List_3->setCurrentIndex(0);

    connect(ui->List_2, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного друга (для attachment)
            this, SLOT(post_attachment(QString)));
    connect(ui->List_3, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранной группы (для attachment)
            this, SLOT(post_attachment(QString)));

    vk_send_attachment * attachment = new vk_send_attachment();

    if(attachment_wall_or_message != 3)
    {
        QString Id_Friend = friend_ids.value(FrName);

        if(attachment_wall_or_message == 0)
        {
            attachment->process_attachment(add_Audio_Id, add_Owner_Id, Id_Friend, Token, 0);
        }
        if(attachment_wall_or_message == 1)
            attachment->process_attachment(add_Audio_Id, add_Owner_Id, Id_Friend, Token, 1);
    }
    else{
        attachment->process_attachment(add_Audio_Id, add_Owner_Id, group_ids.value(FrName), Token, 3);
    }
}

//Удаление файла
void Widget::delete_file()
{
    QFile(temp).remove();
}

//Возможность пролистывания по песни
void Widget::seekable(bool val)
{
    qDebug()<<"seekable: "<<val;
}

//Метаданные
void Widget::metadata()
{
    qDebug()<<"metadata";
    qDebug()<<player->metaData(QMediaMetaData::AudioBitRate);
}

//Доступны метаданные
void Widget::metadataAvailable(bool val)
{
    qDebug()<<"MetadDataAvailableChanged: "<<val;
}

//Показать/ Скрыть уведомления
void Widget::change_show_notif(bool val)
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
    settings->setValue("Show_Notification/val", val);
    settings->sync();
    show_Notif = val;
}

//Сворачивать или нет в трей
void Widget::change_hide_to_tray(bool val)
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
    settings->setValue("Hide_To_Tray/val", val);
    settings->sync();
    Hide_To_Tray = val;
}

//Рисование всех элементов в главном окне
void Widget::DrawGUI()
{
    ui->Photo->hide();

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9);
    shadowEffect->setOffset(3);
    textsong->setGraphicsEffect(shadowEffect);
    ui->tableWidget->setShowGrid(false);

    QString stylesheet_path;

    stylesheet_path = "://CSS/TabWidget.txt";
    ui->tabplaylist->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Label.txt";

    textsong->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->duration->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/LineEdit.txt";
    ui->Search_Line->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/ComboBox.txt";
    ui->List->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->GroupList->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->List_2->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->List_3->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->List_4->setStyleSheet(this->Read_Stylesheet(stylesheet_path));
    ui->List_Albums->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Dial.txt";
    ui->dial->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    ui->dial->installEventFilter(this);
    ui->horizontalSlider->installEventFilter(this);

    stylesheet_path = "://CSS/HorizontalSlider.txt";
    ui->horizontalSlider->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Playlist.txt";
    ui->tableWidget->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Button.txt";

    //Рисование кнопок плеера
    ui->logo->setStyleSheet("border-image: url(:/new/prefix1/icons/logoMini.png) stretch;");
    ui->Frined_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/frends.gif) stretch;");
    ui->GroupButton->setStyleSheet("border-image: url(:/new/prefix1/icons/frends.gif) stretch;");
    ui->Search_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/s.gif) stretch;");
    ui->hideApp->setStyleSheet("border-image: url(:/new/prefix1/icons/down.gif) stretch;");
    ui->Close_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/close.gif) stretch;");
    ui->Set_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/set.gif) stretch;");
    ui->PlayButton->setStyleSheet("border-image: url(:/new/prefix1/icons/play.gif) stretch;");
    ui->NextButton->setStyleSheet("border-image: url(:/new/prefix1/icons/right.gif) stretch;");
    ui->PreviosButton->setStyleSheet("border-image: url(:/new/prefix1/icons/left.gif) stretch;");
    ui->StopButton->setStyleSheet("border-image: url(:/new/prefix1/icons/stop.gif) stretch;");
    ui->repeat_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/rep.gif) stretch;");
    ui->mix_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/mix.gif) stretch;");
    ui->MuteButton->setStyleSheet("border-image: url(:/new/prefix1/icons/should3.gif) stretch;");
    ui->DownloadButton->setStyleSheet("border-image: url(:/new/prefix1/icons/save.gif) stretch;");
    ui->clear_search_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/x.gif) stretch;");
    ui->Open_Albums->setStyleSheet("border-image: url(:/new/prefix1/icons/album.png) stretch;");

    if(status_enable == 1)
        ui->post_Status->setStyleSheet("border-image: url(:/new/prefix1/icons/status_on.png) stretch;");
    else
        ui->post_Status->setStyleSheet("border-image: url(:/new/prefix1/icons/status_off.png) stretch;");

    ui->Lyrics_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/text.png) stretch;");
    ui->Genre_Button->setStyleSheet("border-image: url(:/new/prefix1/icons/note.png) stretch;");
    //Рисование кнопок плеера

    Loading.setStyleSheet(
                "border: 0px solid ;"
                "border-radius: 7px;"
                );
    Loading.setGeometry(160,210,17,17);
    QMovie *movie = new QMovie(":/new/prefix1/icons/loading32.gif");
    Loading.setMovie(movie);

    Loading.show();
    movie->start();

}

//Изменение метаданных
void Widget::metaDataChanged(QString key, QVariant value)
{
    qDebug() << "Metdadata changed:" << key + ":" << value.toString();
}

 //Инициализация сигналов и слотов
void Widget::initialization_SignalSlot()
{

    connect(player, SIGNAL(error(QMediaPlayer::Error)),    //Вывод ошибок engine
            this, SLOT(print_Error_Player(QMediaPlayer::Error)));

    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), //Изменение картинки кнопки плей
            this, SLOT(print_Image_Player_State(QMediaPlayer::State)));

    connect(player, SIGNAL(seekableChanged(bool)),
            this, SLOT(seekable(bool)));

    connect(player, SIGNAL(metaDataChanged()),
            this, SLOT(metadata()));

    connect(player, SIGNAL(metaDataAvailableChanged(bool)),
            this, SLOT(metadataAvailable(bool)));

    connect(player,SIGNAL(durationChanged(qint64)),
            this,SLOT(print_duration(qint64)));                     //ДЛИТЕЛЬНОСТЬ ПЕСНИ

    connect(player, SIGNAL(metaDataChanged(QString,QVariant)),
            this, SLOT(metaDataChanged(QString,QVariant)));

    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(mediaStatusChange(QMediaPlayer::MediaStatus)));

    connect(player, SIGNAL(audioAvailableChanged(bool)),
            this, SLOT(AudioAvailable(bool)));

    connect(ui->List_2, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного друга для отправки песни
            this, SLOT(post_attachment(QString)));

    connect(ui->List_3, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного друга для отправки песни
            this, SLOT(post_attachment(QString)));

    connect(ui->List, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного друга
            this, SLOT(Friends_music(QString)));

    connect(ui->GroupList, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранной группы
            this, SLOT(Groups_music(QString)));

    connect(ui->List_4, SIGNAL(currentTextChanged(QString)),       //Сигнал выбранного жанра популярного
            this, SLOT(process_pop_genre(QString)));

    connect(ui->List_Albums, SIGNAL(currentTextChanged(QString)),
            this, SLOT(selected_album(QString)));

    connect(audiopop, SIGNAL(send_photo( QPair<QString, QString>)), //Получние фото друга
            this, SLOT(print_nameFriend_andPhoto( QPair<QString, QString>)));

    connect(audiopop, SIGNAL(send_group_id(QString)),           //Создание вкладки группы
            this, SLOT(print_nameGroup_andPhoto(QString)));

    connect(audiopop, SIGNAL(signal_create_newTab()),
            this, SLOT(print_newAlbumTab()));

    connect(audiopop, SIGNAL(audio_table( QList< QPair<QString, QString> >,QList< QPair<QString, QString> >, QList< QPair<QString, QString> >, QList< QPair<QString, QString> >)), //Получение плэйлиста
            this, SLOT(print_audioTable( QList< QPair<QString, QString> >, QList< QPair<QString, QString> >, QList< QPair<QString, QString> >, QList< QPair<QString, QString> >)));

    connect(ui->dial,SIGNAL(valueChanged(int)),
             player,SLOT(setVolume(int)));                       //ГРОМКОСТЬ

    connect(ui->dial,SIGNAL(valueChanged(int)),
            this, SLOT(print_volume_icon(int)));                //Изменение иконки громкости   

    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), //Выбор песни по 2х нажатию
            this, SLOT(selectedItem(QTableWidgetItem*)));

    connect(this, SIGNAL(PlaySong(QString, int)),                      //Сигнал изменения песни
            this, SLOT(PlaylingSong(QString, int)));

    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));                       //Сигнал изменения вкладки(плейэлиста)

    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)), //Сигнал при нажатии на икноку в трее
              this,SLOT(ActivationTray(QSystemTrayIcon::ActivationReason)));

    connect(ui->Search_Line, SIGNAL(returnPressed()),            //Нажатие Enter в поле поиска
            this,SLOT(on_Search_BTN_clicked()));

    connect(ui->Search_Line,SIGNAL(selectionChanged()),          //Очистить строку посика
            ui->Search_Line,SLOT(clear()));

    //Сигналы и слоты Слайдера песни
    //connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(positionTHREE()));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionREVERS(qint64)));
   // connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(positionTWO(int)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(print_time_song(qint64)));
   // connect(ui->horizontalSlider,SIGNAL(sliderPressed()),this,SLOT(position()));
    //Сигналы и слоты Слайдера песни
}

//Генерация ID программы
void Widget::generation_Id_Program()
{
    long int Id_key_int = qrand() % 99999;
    QString Id_key = QString::number(Id_key_int);
    QString Id_Mac = QNetworkInterface::allInterfaces().first().hardwareAddress();
    Id_Mac.replace(":","");
    Id_PR = Id_key + Id_Mac;

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    if(settings->value("Id/value").toInt() == 1){
        settings->setValue("Id/value", Id_PR);
        settings->sync();
    }
    else{
        Id_PR = settings->value("Id/value").toString();
    }
}

//Выводит доступность новой версии
void Widget::printNewVersion(bool val)
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    if(val)
    {
        Messages * messages = new Messages;
        QString title, text;
        title = "Обновление";
        text = "Доступно Обновление. Перейдите в Настройки для обновления";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        ui->UpdateInformation->show();
        ui->UpdateInformation->setStyleSheet(
                    "background-color:rgb(37, 37, 37);"
                     "color : white;"
                    "border: 1px solid rgb(47, 126, 165);"
                    "border-radius: 15px;"
                "padding: 1px;"
                                    );

        settings->setValue("Update/Val", 1);
        settings->sync();
    }
    else
    {
        ui->UpdateInformation->hide();

        settings->setValue("Update/Val", 0);
        settings->sync();
    }
}

//Открывает updater
void Widget::ApplyNew()
{   
    try
    {
        QProcess *vec = new QProcess();
        qDebug()<<vec->startDetached("updater.exe");
        connect(vec, SIGNAL(started()),
                this, SLOT(CloseToUpdate()));
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error update");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }
}

//Закрывает прогу
void Widget::CloseToUpdate()
{   
        delete this;
        delete trIcon;
        delete osd;
        exit(0);
}

//Запуск закачки новой версии
void Widget::CreateUpdater()
{
    try
    {
        UpdateVersion * Update = new UpdateVersion();
        connect(Update, SIGNAL(Restarting()),
                this, SLOT(ApplyNew()));
        Update->StartUpdate();
    }
    catch(QException)
    {
        QMessageBox msgBox;
        msgBox.setText("Error Update");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }
}

//Инициализация трэя
void Widget::initialization_Tray()
{
    trIcon = new QSystemTrayIcon();                     //инициализируем иконку

    QMenu *trayMenu=new QMenu("VKPlayer");
    trayMenu->setStyleSheet(
                "QMenu {"
                "background-color: rgb(29, 29, 29);"
                "border-radius: 9px;"
                "border: 1px solid black;"
                "color: white;"

            "}"
            "QMenu::item:selected {"
                "background: rgb(80, 80, 80);"
            "}"
                );

    QAction *PlayPause=new QAction(QIcon(":/new/prefix1/icons/play.gif"),"Плей/Пауза",trayMenu);
    PlayPause->setIconVisibleInMenu(true);
    connect(PlayPause, SIGNAL(triggered()),this, SLOT(on_PlayButton_clicked()));

    QAction *NextSong=new QAction(QIcon(":/new/prefix1/icons/right.gif"),"Следующая",trayMenu);
    NextSong->setIconVisibleInMenu(true);
    connect(NextSong,SIGNAL(triggered()),this, SLOT(on_NextButton_clicked()));

    QAction *PreviousSong=new QAction(QIcon(":/new/prefix1/icons/left.gif"),"Предыдущая",trayMenu);
    PreviousSong->setIconVisibleInMenu(true);
    connect(PreviousSong,SIGNAL(triggered()),this, SLOT(on_PreviosButton_clicked()));

    QAction *Settings=new QAction(QIcon(":/new/prefix1/icons/set.gif"),"Настройки",trayMenu);
    Settings->setIconVisibleInMenu(true);
    connect(Settings,SIGNAL(triggered()),this, SLOT(on_Set_BTN_clicked()));

    QAction *Exit=new QAction(QIcon(":/new/prefix1/icons/close.gif"),"Выход",trayMenu);
    Exit->setIconVisibleInMenu(true);
    connect(Exit,SIGNAL(triggered()),this, SLOT(on_Close_BTN_clicked()));

    trayMenu->addAction(PlayPause);
    trayMenu->addAction(NextSong);
    trayMenu->addAction(PreviousSong);
    trayMenu->addAction(Settings);
    trayMenu->addAction(Exit);

    trIcon->setContextMenu(trayMenu);
    trIcon->setIcon(QIcon(QPixmap(":/new/prefix1/icons/play.gif")));  //устанавливаем иконку
    trIcon->show();                                     //отображаем объект
}

//Получение токена и айди от окна авторизации
void Widget::getTokenAndUsID(QString token, QString Id)
{
    Token = token;
    UsId = Id;
    ui->tabplaylist->setEnabled(false);
    ui->List->setEnabled(false);
    ui->GroupList->setEnabled(false);
    ui->Search_Line->setEnabled(false);
    ui->Genre_Button->setEnabled(false);


    this->get_User_Avatar(); //Получить аватарку пользователя
    this->start_group_VK(); //Вступление в группу.
    this->post_User_trackVisitor(); // Добавить данные о посещаемости пользователя

    ConnectToServer * SendUsId = new ConnectToServer();  //Отпрвка id пользователя на сервер разработчика
    connect(this, SIGNAL(click_download_music()), SendUsId, SLOT(send_Download_music()));
   /* QThread * thread = new QThread;
    SendUsId->moveToThread(thread);
    thread->start();*/
}

//обработка нажатия кнопки "Play" в зависимости от состояния плеера
void Widget::on_PlayButton_clicked()
{
    QRect rect = ui->PlayButton->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->PlayButton, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+15, Y+15, 1, 1));
     animation->setEndValue(QRect(X, Y, 30, 30));
     animation->start();

    QMediaPlayer::State state = player->state();
    switch(state){

    case QMediaPlayer::PlayingState:
        player->pause();
        break;

    case QMediaPlayer::PausedState:
        player->play();
        break;

    case QMediaPlayer::StoppedState:       
        PlayMusic = "Home";
        int RowDoubleClick = 0;
        emit PlaySong(PlayMusic, RowDoubleClick);
        break;
    }
}

//Нажатие на кнопку "Следующая"
void Widget::on_NextButton_clicked()
{
    QRect rect = ui->NextButton->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->NextButton, "geometry");
    connect(animation, SIGNAL(finished()), this, SLOT(AnimationNextButton()));

    animation->setDuration(100);
    animation->setStartValue(QRect(X+15, Y+15, 1, 1));
    animation->setEndValue(QRect(X, Y, 30, 30));
    animation->start();
}

//Конец Анимации следующий песни
void Widget::AnimationNextButton(){
    PlayMusic = "Next";                                  //СЛЕДУЮЩАЯ ПЕСНЯ
    int RowDoubleClick = 0;
    emit PlaylingSong(PlayMusic, RowDoubleClick);
}

//Обработка изменение Статуса плеера
void Widget::mediaStatusChange(QMediaPlayer::MediaStatus status)
{
    qDebug()<<status;

    switch(status){

    case QMediaPlayer::BufferedMedia:

        break;

    case QMediaPlayer::EndOfMedia:
        this->on_NextButton_clicked();
        break;

    case QMediaPlayer::UnknownMediaStatus:

        break;

    case QMediaPlayer::LoadingMedia:
        break;

    case QMediaPlayer::LoadedMedia:

        break;

    case QMediaPlayer::StalledMedia:
        break;

    case QMediaPlayer::BufferingMedia:
        break;

    case QMediaPlayer::InvalidMedia:

        break;

    case QMediaPlayer::NoMedia:
        break;
    }
}

//Нажатие на кнопку "Предыдущая"
void Widget::on_PreviosButton_clicked()
{
    QRect rect = ui->PreviosButton->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->PreviosButton, "geometry");
    connect(animation, SIGNAL(finished()), this, SLOT(AnimationPreviousButton()));

    animation->setDuration(100);
    animation->setStartValue(QRect(X+15, Y+15, 1, 1));
    animation->setEndValue(QRect(X, Y, 30, 30));
    animation->start();
}

//Конец анимации предыдущей песни
void Widget::AnimationPreviousButton(){
    PlayMusic = "Previous";                             //ПРЕДЫДУЩАЯ ПЕСНЯ
    int RowDoubleClick = 0;
    emit PlaylingSong(PlayMusic, RowDoubleClick);
}

//Нажатие на кнопку "СТОП"
void Widget::on_StopButton_clicked()
{
    QRect rect = ui->StopButton->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->StopButton, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+15, Y+15, 1, 1));
     animation->setEndValue(QRect(X, Y, 30, 30));
     animation->start();

    player->stop();                                    //СТОП
}

//Формирование запроса на смену плэйлиста
void Widget::changedPlaylist(QUrl current, int flag, int Friend_or_Group, QString flag_genre_pop)                      //Посылание запроса на получениe плэйлиста
{
    create_tab = true;

        QString S;
        int MyFlag;

        Loading.show();

        ui->tabplaylist->setEnabled(false);
        ui->List->setEnabled(false);
        ui->GroupList->setEnabled(false);
        ui->Search_Line->setEnabled(false);
        ui->Genre_Button->setEnabled(false);

            ui->tableWidget->clear();


        if(flag == 0)
        {
            MyFlag = 0;        //флаг чтобы объект vk_audiopop знал мои это аудиозаписи или нет

            tmp_ID = UsId;
            tmp_CURRENT = current;
            tmp_FOUR = flag_genre_pop;
            tmp_MYFLAG = MyFlag;
            tmp_SIX = 0;

            offset = 0;
            audiopop->get_audioPOPULAR(UsId,Token,current, flag_genre_pop, MyFlag, 0, 0);
        }
        else if (flag == 3)
        {
            MyFlag = 3;

            tmp_ID = UsId;
            tmp_CURRENT = current;
            tmp_FOUR = temp_albumId;
            tmp_MYFLAG = MyFlag;
            tmp_SIX = 3;
            offset = 0;

            audiopop->get_audioPOPULAR(UsId,Token,current,temp_albumId, MyFlag, tmp_SIX, 0);
        }
        else
        {
            MyFlag = 1;
            if(Friend_or_Group == 1){

                tmp_ID = temp_frId;
                tmp_CURRENT = current;
                tmp_FOUR = S;
                tmp_MYFLAG = MyFlag;
                tmp_SIX = 1;
                offset = 0;

                audiopop->get_audioPOPULAR(temp_frId,Token,current,S, MyFlag, 1, 0);
            }
            if(Friend_or_Group == 2){

                tmp_ID = temp_grId;
                tmp_CURRENT = current;
                tmp_FOUR = S;
                tmp_MYFLAG = MyFlag;
                tmp_SIX = 2;
                offset = 0;

                audiopop->get_audioPOPULAR(temp_grId,Token,current,S, MyFlag, 2, 0);
            }

        }
}

//Посыл запроса на получение плйэлиста при нажатие кнопки "Search"
void Widget::SearchMusic(QString tmp)
{
    create_tab = true;

    QWidget *newTab = new QWidget(ui->tabplaylist);


    QString SearchTmpShort;
    if(tmp.size() > 12)
    {
        for(int i = 0 ; i < 10 ; i++)
        {
            SearchTmpShort[i] = tmp[i];
        }
        SearchTmpShort = SearchTmpShort + "...";
        ui->tabplaylist->addTab(newTab,SearchTmpShort);
    }
    else
        ui->tabplaylist->addTab(newTab, tmp);

    ui->tabplaylist->setCurrentIndex(3);
    ui->tabplaylist->setEnabled(false);
    QUrl current("https://api.vk.com/method/audio.search");

        ui->tableWidget->clear();


    int MyFlag = 0;        //флаг чтобы объект vk_audiopop знал мои это аудиозаписи или нет

    Loading.show();
    ui->tabplaylist->setEnabled(false);
    ui->List->setEnabled(false);
    ui->GroupList->setEnabled(false);
    ui->Search_Line->setEnabled(false);
    ui->Genre_Button->setEnabled(false);

    tmp_ID = UsId;
    tmp_CURRENT = current;
    tmp_FOUR = tmp;
    tmp_MYFLAG = MyFlag;
    tmp_SIX = 0;
    offset = 0;

    audiopop->get_audioPOPULAR(UsId,Token,current,tmp,MyFlag,0, 0);
}

//Выкл/Вкл звука
void Widget::on_MuteButton_clicked()
{
    QRect rect = ui->MuteButton->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->MuteButton, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+9, Y+9, 1, 1));
     animation->setEndValue(QRect(X, Y, 19, 19));
     animation->start();

    if(player->isMuted())
    {
        player->setMuted(false);
        ui->MuteButton->setStyleSheet("border-image: url(:/new/prefix1/icons/should2.gif) stretch;");

    }
    else
    {
         player->setMuted(true);
        ui->MuteButton->setStyleSheet("border-image: url(:/new/prefix1/icons/not_should.gif) stretch;");
    }
}

//Кнопка Загрузить
void Widget::on_DownloadButton_clicked()
{
    QRect rect = ui->DownloadButton->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->DownloadButton, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+9, Y+9, 1, 1));
     animation->setEndValue(QRect(X, Y, 19, 19));
     animation->start();

    QString a, b, c;
    this->Download_fuction(1, a, b, c);
}

//Включение кнопки "Загрузка"
void Widget::Complete_D()
{
    ui->DownloadButton->setStyleSheet("border-image: url(:/new/prefix1/icons/save2.gif) stretch;");
    ui->DownloadButton->setEnabled(true);
    emit complete_Download_Song();
}

//Установить цвет R
void Widget::setColor_R(int r)
{
    R = r;
    QString styleSheet = "Widget { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(R).arg(G).arg(B));
    QString styleSheet1 = "background-color : rgb(%1, %2, %3)";
    osd->set_background_color(QColor(R,G,B));
}

//Установить цвет G
void Widget::setColor_G(int g)
{
    G = g;
    QString styleSheet = "Widget { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(R).arg(G).arg(B));
    QString styleSheet1 = "background-color : rgb(%1, %2, %3)";
    osd->set_background_color(QColor(R,G,B));
}

//Установить цвет B
void Widget::setColor_B(int b)
{
    B = b;
    QString styleSheet = "Widget { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(R).arg(G).arg(B));
    QString styleSheet1 = "background-color : rgb(%1, %2, %3)";
    osd->set_background_color(QColor(R,G,B));
}

//Установить цвет Default
void Widget::standatColor()
{
    B = G = R = 49;
    QString styleSheet = "Widget { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(R).arg(G).arg(B));
    QString styleSheet1 = "background-color : rgb(%1, %2, %3)";
    osd->set_background_color(QColor(R,G,B));
}

//Загрузка настроек плеера
void Widget::download_settings()
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    ui->dial->setValue(settings->value("Volume/val").toInt());             //Установить громкость
    player->setVolume(settings->value("Volume/val").toInt());
    R = settings->value("Color/R").toInt();
    G = settings->value("Color/G").toInt();
    B = settings->value("Color/B").toInt();
    tran = settings->value("WindowOpacity/tran").toFloat();

    directory = settings->value("Directory/string").toString();

    SpeedText = settings->value("TextSongSpeed/val").toInt();
    textsong->setSpeed(SpeedText);

    show_Notif = settings->value("Show_Notification/val").toBool();
    status_enable = settings->value("Status_Enable/val").toInt();
    Hide_To_Tray = settings->value("Hide_To_Tray/val").toBool();

    this->setWindowOpacity(0);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(800);
    animation->setStartValue(0);
    animation->setEndValue(tran);
    animation->start();

    ui->List_2->hide();
    ui->List_3->hide();
    ui->List_4->hide();
    ui->List_Albums->hide();
}

//Изменение вкладки плеэйлиста
void Widget::changePlaylist(int index)
{
    if(index == 0)
    {
        ui->PhotoFriend->hide();
        ui->PhotoGroup->hide();

        ui->tabplaylist->setEnabled(false);
        this->Popularplaylist();
        flag_if_MyPlaylist_isPlaying = false;
        flag_if_RecomendationPlaylist = false;
    }
    if(index == 1)
    {
        ui->PhotoFriend->hide();
        ui->PhotoGroup->hide();

        ui->tabplaylist->setEnabled(false);
        this->Myplaylist();
        flag_if_MyPlaylist_isPlaying = true;
        flag_if_RecomendationPlaylist = false;
    }
    if(index == 2)
    {
        ui->PhotoFriend->hide();
        ui->PhotoGroup->hide();

        ui->tabplaylist->setEnabled(false);
        this->RecomPlaylist();
        flag_if_MyPlaylist_isPlaying = false;
        flag_if_RecomendationPlaylist = true;
    }

}

//Запрос на получение мои аудиозаписей
void Widget::Myplaylist()
{
    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));

    int flag = 0;
    QUrl current("https://api.vk.com/method/audio.get");
    this->changedPlaylist(current, flag, 0, " ");
}

 //Запрос на получени популярного плэйлиста
void Widget::Popularplaylist()
{
    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));

    int flag = 0;
    QUrl current("https://api.vk.com/method/audio.getPopular");
    this->changedPlaylist(current, flag, 0, "empty");

}

//Запрос на получение рекомедованных композиций
void Widget::RecomPlaylist()
{
    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));

    int flag = 0;
    QUrl current("https://api.vk.com/method/audio.getRecommendations");
    this->changedPlaylist(current, flag, 0, " ");
}

//Выход из аккаунта
void Widget::exit_Account()
{
    this->saveGeom("Main");
    player->stop();
    this->close();
    delete trIcon;
    delete player;

    auther * Auther = new auther;
    Auther->chech_auth();
    delete this;
}

//Загрузка музыки
void Widget::Download_fuction(int flag, QString artist, QString title, QString url)
{
    Download * download = new Download();                          //Объект класса "Загрузка"
    connect(download,SIGNAL(complete()),                           //Завершение загрузки композиции
            this,SLOT(Complete_D()));
    connect(this, SIGNAL(complete_Download_Song()),
            download, SLOT(deleteLater()));


    if(directory.isEmpty() || !QDir(directory).exists())
    {
        Messages *messages = new Messages;
        QString title, text;

        title = "Ошибка";
        text = "Выберите папку для загрузки в Настройках - вкладка Общие";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        return;
    }

    if(flag == 1){
        QString correctedArtist = Artist_song.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
        QString correctedTitle = Title_song.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
        QString fullName = correctedArtist + "_" + correctedTitle;
        if(fullName.size()>140){
            temp = directory + "/" + fullName.mid(0,140) + ".mp3";
        }
        else
            temp = directory + "/" + fullName + ".mp3";         //Если нажали кнопку
    }

    if(flag == 2){
        QString correctedArtist = artist.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
        QString correctedTitle = title.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
        QString fullName = correctedArtist + "_" + correctedTitle;
        if(fullName.size()>140){
            temp = directory + "/" + fullName.mid(0,140) + ".mp3";
        }
        else
            temp = directory + "/" + fullName + ".mp3";        //Если выбрали в контекстном меню
    }


    if (QFile::exists(temp) )
    {
        Messages *messages = new Messages;
        connect(messages, SIGNAL(click_ReWrite()), this, SLOT(delete_file()));
        QString title, text;

        title = "Загрузка";
        text = "Файл с таким именем уже существует. Удалить?";
        messages->set_Title_and_Text(title, text, false, true);
        messages->show();
    }
    else
    {
        ui->DownloadButton->setEnabled(false);

        emit click_download_music();

        if(flag == 1)
            download->reciveDoc(Url_song , temp, Artist_song + Title_song);
        if(flag == 2)
            download->reciveDoc(url , temp, tmpArtist + " - " + tmpTitle);
    }

}

//Нажатие на кнопку "Поиск"
void Widget::on_Search_BTN_clicked()
{
    QRect rect = ui->Search_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Search_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+10, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 20, 20));
     animation->start();

    ui->Search_Line->setEnabled(false);

    ui->PhotoFriend->hide();
    ui->PhotoGroup->hide();

    disconnect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));
    ui->tabplaylist->removeTab(3);
    connect(ui->tabplaylist,SIGNAL(currentChanged(int)),
             this, SLOT(changePlaylist(int)));

    QString tmp = ui->Search_Line->text();
    ui->Search_Line->clear();
    this->SearchMusic(tmp);
    flag_if_MyPlaylist_isPlaying = false;
    flag_if_RecomendationPlaylist = false;
    ui->Search_Line->setText(" Поиск музыки");
}

//Нажатие на кнопку "Очистить строку поиска"
void Widget::on_clear_search_BTN_clicked()
{
    ui->Search_Line->clear();
}

//Выбор директории загрузки файла
void Widget::MenuChooseDirectory(QString Dir)
{
    directory = Dir;
}

//Нажатие на кнопку "Настройки"
void Widget::on_Set_BTN_clicked()
{
    QRect rect = ui->Set_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Set_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+10, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 20, 20));
     animation->start();

    Settings * settings = new Settings;
    this->setEnabled(false);
    connect(settings,SIGNAL(sEnabled(bool)),this,SLOT(setEnabled(bool)));
    settings->show();
    connect(settings,SIGNAL(valueR(int)),this,SLOT(setColor_R(int)));
    connect(settings,SIGNAL(valueG(int)),this,SLOT(setColor_G(int)));
    connect(settings,SIGNAL(valueB(int)),this,SLOT(setColor_B(int)));
    connect(settings,SIGNAL(standartC()),this,SLOT(standatColor()));
    connect(settings,SIGNAL(Transpar(int)),this,SLOT(transparency(int)));
    connect(settings, SIGNAL(StartDownloadNewVersion()), this, SLOT(CreateUpdater()));
    connect(settings,SIGNAL(exit_ACC()),this,SLOT(exit_Account()));
    connect(settings, SIGNAL(Directory(QString)),this, SLOT(MenuChooseDirectory(QString)));
    connect(settings, SIGNAL(ChangeSpeedText(int)), textsong, SLOT(setSpeed(int)));
    connect(settings, SIGNAL(ChangeNotification(bool)), this, SLOT(change_show_notif(bool)));
    connect(settings, SIGNAL(ChangeHideToTray(bool)), this, SLOT(change_hide_to_tray(bool)));
    connect(settings, SIGNAL(send_new_hotkey(int,int,int)), this, SLOT(register_inregister_hotkey(int,int,int)));
}

//Вкл. и Выкл. Режима "В перемешку"
void Widget::on_mix_BTN_clicked()
{
    QRect rect = ui->mix_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->mix_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+9, Y+9, 1, 1));
     animation->setEndValue(QRect(X, Y, 19, 19));
     animation->start();

    if((sequence == "NoRandom") || (sequence == "Repeat") || (sequence == "NoRepeat"))
    {
        sequence = "Random";
        ui->mix_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/not_mix.gif) stretch;");
        ui->repeat_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/rep.gif) stretch;");
    }
    else
    {
        sequence = "NoRandom";
        ui->mix_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/mix.gif) stretch;");
    }


}

//Вкл/Выкл режима "повторять композицию"
void Widget::on_repeat_BTN_clicked()
{
    QRect rect = ui->repeat_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->repeat_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+9, Y+9, 1, 1));
     animation->setEndValue(QRect(X, Y, 19, 19));
     animation->start();

    if((sequence == "NoRepeat") || (sequence == "NoRandom") || (sequence == "Random"))
    {
        sequence = "Repeat";
        ui->repeat_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/not_rep.gif) stretch;");
        ui->mix_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/mix.gif) stretch;");
    }
    else
    {
        sequence = "NoRepeat";
        ui->repeat_BTN->setStyleSheet("border-image: url(:/new/prefix1/icons/rep.gif) stretch;");
    }

}

//Переход в трей или свернуть
void Widget::on_hideApp_clicked()
{
    if(Hide_To_Tray)
        this->close();
    else
        this->showMinimized();
}

//Закрытие приложения
void Widget::on_Close_BTN_clicked()
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    settings->setValue("Volume/val", ui->dial->value());
    settings->sync();

    QRect rect = ui->Close_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Close_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+10, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 20, 20));
     animation->start();

     this->saveGeom("Main");

    trIcon->hide();
    delete trIcon;
    delete osd;
    exit(0);
}

//Нажатие на кнопку "текст песни"
void Widget::on_Lyrics_BTN_clicked()
{
    ui->Lyrics_BTN->setEnabled(false);

    QRect rect = ui->Lyrics_BTN->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Lyrics_BTN, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+10, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 20, 20));
     animation->start();

     lyrics_out * lyrics_out_text = new lyrics_out();
     lyrics_out_text->show();

    vk_lyrics * lyrics = new vk_lyrics;
    connect(lyrics, SIGNAL(send_lyrics(QString)),
            lyrics_out_text, SLOT(out_Text_Song(QString)));
    connect(lyrics_out_text, SIGNAL(complete_recieving()), lyrics, SLOT(deleteLater()));
    connect(lyrics_out_text, SIGNAL(close_lyrics(bool)),
            ui->Lyrics_BTN, SLOT(setEnabled(bool)));

    lyrics->get_lyrics(Lyrics_Id_song, Token);
}

//Запрос на установление статуса
void Widget::install_status()
{
    vk_post_status * Status = new vk_post_status();

    ui->post_Status->setEnabled(false);

    connect(Status, SIGNAL(send_result()),
            this, SLOT(print_enable_status()));
    connect(this, SIGNAL(complete_Install_status()),
            Status, SLOT(deleteLater()));

    if(status_enable == 1)
    {
        Status->ins_status(Id_song, Owner_Id_song, Token);
    }
    else
    {
        QString null;
        Status->ins_status(null, null, Token);
    }

}

//Разблокировка кнопки статуса после включения
void Widget::print_enable_status()
{
    ui->post_Status->setEnabled(true);
    emit complete_Install_status();
}

//Нажатие на кнопку "Установить статус"
void Widget::on_post_Status_clicked()
{
    QRect rect = ui->post_Status->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->post_Status, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+10, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 20, 20));
     animation->start();

    if(status_enable == 0)
    {
        ui->post_Status->setStyleSheet("border-image: url(:/new/prefix1/icons/status_on.png) stretch;");
        status_enable = 1;
        osd->SetMessage("VKPlayer", "Трансляция в статус - ON", QImage(":/new/prefix1/vk.ico"));

        if(show_Notif)
            osd->show();
    }
    else
    {
        ui->post_Status->setStyleSheet("border-image: url(:/new/prefix1/icons/status_off.png) stretch;");
        status_enable = 0;
        osd->SetMessage("VKPlayer", "Трансляция в статус - OFF", QImage(":/new/prefix1/vk.ico"));
        if(show_Notif)
            osd->show();
    }

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
    settings->setValue("Status_Enable/val", status_enable);

    ui->post_Status->setEnabled(false);
    this->install_status();   
}

//Нажатие на кнопку "Поддержать"
void Widget::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://money.yandex.ru/embed/small.xml?account=41001930308848&quickpay=small&yamoney-payment-type=on&button-text=06&button-size=l&button-color=white&targets=%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%BA%D0%B0+%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B0+VKPlayer&default-sum=100"));
}

//Нажатие на кнопку "Выбрать жанр популярной музыки"
void Widget::on_Genre_Button_clicked()
{
    QRect rect = ui->Genre_Button->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Genre_Button, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+10, Y+10, 1, 1));
     animation->setEndValue(QRect(X, Y, 20, 20));
     animation->start();
     ui->List_4->showPopup();
}

void Widget::click_next_300()
{
    ui->tabplaylist->setEnabled(false);
    ui->List->setEnabled(false);
    ui->GroupList->setEnabled(false);
    ui->Search_Line->setEnabled(false);
    ui->Genre_Button->setEnabled(false);

    create_tab = false;
    ui->tableWidget->clear();
    Loading.show();

    offset = offset + 150;
    audiopop->get_audioPOPULAR(tmp_ID,Token,tmp_CURRENT,tmp_FOUR,tmp_MYFLAG,tmp_SIX, offset);
}

void Widget::click_previous_300()
{
    ui->tabplaylist->setEnabled(false);
    ui->List->setEnabled(false);
    ui->GroupList->setEnabled(false);
    ui->Search_Line->setEnabled(false);
    ui->Genre_Button->setEnabled(false);

    create_tab = false;
    ui->tableWidget->clear();
    Loading.show();

    offset = offset - 150;
    audiopop->get_audioPOPULAR(tmp_ID,Token,tmp_CURRENT,tmp_FOUR,tmp_MYFLAG,tmp_SIX, offset);
}

void Widget::on_Open_Albums_clicked()
{
    QRect rect = ui->Open_Albums->geometry();
    int X = rect.x();
    int Y = rect.y();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Open_Albums, "geometry");
    animation->setDuration(100);
     animation->setStartValue(QRect(X+15, Y+9, 1, 1));
     animation->setEndValue(QRect(X, Y, 30, 18));
     animation->start();
     ui->List_Albums->showPopup();
}
