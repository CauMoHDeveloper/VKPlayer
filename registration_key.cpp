#include "registration_key.h"
#include "ui_registration_key.h"

Registration_Key::Registration_Key(WidgetParent *parent) :
    WidgetParent(parent),
    ui(new Ui::Registration_Key)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    this->DrawGUI();

    Keys_event = new QSet<int>;
    flag_Key_One_true = false;
    flag_Key_Two_true = false;
    flag_Apply = false;

    this->filling_hotkey();

    this->setRoundedCorners(6,6,6,6);

    this->setWindowOpacity(0);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(0);
    animation->setEndValue(0.99);
    animation->start();
}

Registration_Key::~Registration_Key()
{
    delete ui;
}

void Registration_Key::keyPressEvent(QKeyEvent *event)
{
     Keys_event->insert(event->nativeVirtualKey());
     if (Keys_event->count() == 2) {
         flag_Apply = false;
         flag_Key_One_true = false;
         flag_Key_Two_true = false;
         Key_One.clear();
         Key_Two.clear();
         ui->this_keys->clear();

         int k = 0;
         QSet<int>::iterator i;
         for (i = Keys_event->begin(); i != Keys_event->end(); ++i){

             QHashIterator<int, QString> Iter(myMapKey);
                 while(Iter.hasNext())
                 {
                     Iter.next();
                     if(Iter.key() == *i){

                          ui->this_keys->insert(Iter.value());

                          if(k == 0){
                             ui->this_keys->insert(" + ");
                             Key_One = Iter.value() ;
                             if(Key_One=="Alt"||Key_One=="Ctrl"||Key_One=="Shift")
                                flag_Key_One_true = true;

                             id_Key_One = *i;
                          }

                          if(k == 1){
                             Key_Two = Iter.value();
                             if(Key_Two=="Alt"||Key_Two=="Ctrl"||Key_Two=="Shift")
                                flag_Key_Two_true = true;

                             id_Key_two = *i;
                          }
                     }
                 }

              k++;
         }

         if(!flag_Key_One_true && !flag_Key_Two_true)
         {
             Keys_event->clear();
             Messages * messages = new Messages;
             messages->set_Title_and_Text("Ошибка", "Должен быть один из модификаторов ('Alt', 'Shift', 'Ctrl')",  false, false);
             messages->show();
             return;
         }
         else if(flag_Key_One_true && flag_Key_Two_true){
             Keys_event->clear();
             Messages * messages = new Messages;
             messages->set_Title_and_Text("Ошибка", "Только ОДИН из ('Alt', 'Shift', 'Ctrl')",  false, false);
             messages->show();
             return;
         }
         else{
             if(flag_Key_Two_true){
                 QString tmp;
                 int temp;
                 tmp = Key_One;
                 Key_One = Key_Two;
                 Key_Two = tmp;

                 temp = id_Key_One;
                 id_Key_One = id_Key_two;
                 id_Key_two = temp;
             }

             Keys_event->clear();

             if(Key_One=="Alt")
                 id_Key_One = 1;
             if(Key_One=="Ctrl")
                 id_Key_One = 2;
             if(Key_One=="Shift")
                 id_Key_One = 4;

             flag_Apply = true;
         }


     }
}

void Registration_Key::keyReleaseEvent(QKeyEvent *event)
{
   Keys_event->remove((event->nativeVirtualKey()));
}

void Registration_Key::DrawGUI()
{
    ui->this_keys->setAlignment(Qt::AlignCenter);

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    int r = settings->value("Color/R").toInt();
    int g = settings->value("Color/G").toInt();
    int b = settings->value("Color/B").toInt();
    QString styleSheet = "Registration_Key { background-color : rgb(%1, %2, %3)}";
    this->setStyleSheet(styleSheet.arg(r).arg(g).arg(b));

    ui->CloseApp->setStyleSheet("border-image: url(:/new/prefix1/icons/close.gif) stretch;");

    QString stylesheet_path;

    stylesheet_path =  "://CSS/MessageText.txt";
    ui->Text->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/Button.txt";
    ui->register_hothey->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    stylesheet_path = "://CSS/LineEdit.txt";
    ui->this_keys->setStyleSheet(this->Read_Stylesheet(stylesheet_path));

    ui->Title->setStyleSheet(
                "color:white;"
                );

    ui->Icon->setStyleSheet("border-image: url(:/new/prefix1/vk.ico) stretch;");
}

void Registration_Key::filling_hotkey()
{
    myMapKey.insert(8, "Backspace"); myMapKey.insert(9, "Tab");myMapKey.insert(13, "Enter");
    myMapKey.insert(16, "Shift"); myMapKey.insert(17, "Ctrl");myMapKey.insert(18, "Alt");
    myMapKey.insert(19, "Pause");myMapKey.insert(20, "CapsLock"); myMapKey.insert(27, "Esc");
    myMapKey.insert(32, "Space");myMapKey.insert(33, "PageUp");myMapKey.insert(34, "PageDown");
    myMapKey.insert(35, "End");myMapKey.insert(36, "Home");myMapKey.insert(37, "Left");
    myMapKey.insert(38, "Up");myMapKey.insert(39, "Right");myMapKey.insert(40, "Down");
    myMapKey.insert(45, "Insert");myMapKey.insert(46, "Delete");myMapKey.insert(48, "0");
    myMapKey.insert(49, "1"); myMapKey.insert(50, "2"); myMapKey.insert(51, "3");
    myMapKey.insert(52, "4");myMapKey.insert(53, "5");myMapKey.insert(54, "6");
    myMapKey.insert(55, "7"); myMapKey.insert(56, "8");myMapKey.insert(57, "9");
    myMapKey.insert(65, "A");myMapKey.insert(66, "B");myMapKey.insert(67, "C");
    myMapKey.insert(68, "D"); myMapKey.insert(69, "E"); myMapKey.insert(70, "F");
    myMapKey.insert(71, "G"); myMapKey.insert(72, "H"); myMapKey.insert(73, "I");
    myMapKey.insert(74, "J");myMapKey.insert(75, "K");myMapKey.insert(76, "L");
    myMapKey.insert(77, "M");myMapKey.insert(78, "N");myMapKey.insert(79, "O");
    myMapKey.insert(80, "P");myMapKey.insert(81, "Q"); myMapKey.insert(82, "R");
    myMapKey.insert(83, "S");myMapKey.insert(84, "T");myMapKey.insert(85, "U");
    myMapKey.insert(86, "V");myMapKey.insert(87, "W");myMapKey.insert(88, "X");
    myMapKey.insert(89, "Y");myMapKey.insert(90, "Z");myMapKey.insert(91, "LeftWindows");
    myMapKey.insert(92, "RightWindows");myMapKey.insert(93, "Applications");myMapKey.insert(96, "NumPad 0");
    myMapKey.insert(97, "NumPad 1"); myMapKey.insert(98, "NumPad 2"); myMapKey.insert(99, "NumPad 3");
    myMapKey.insert(100, "NumPad 4"); myMapKey.insert(101, "NumPad 5");myMapKey.insert(102, "NumPad 6");
    myMapKey.insert(103, "NumPad 7");myMapKey.insert(104, "NumPad 8");myMapKey.insert(105, "NumPad 9");
    myMapKey.insert(106, "NumPad *"); myMapKey.insert(107, "NumPad +"); myMapKey.insert(109, "NumPad -");
    myMapKey.insert(110, "NumPad ."); myMapKey.insert(111, "NumPad /");myMapKey.insert(112, "F1");
    myMapKey.insert(113, "F2");myMapKey.insert(114, "F3"); myMapKey.insert(115, "F4");
    myMapKey.insert(116, "F5"); myMapKey.insert(117, "F6");myMapKey.insert(118, "F7");
    myMapKey.insert(119, "F8");myMapKey.insert(120, "F9");myMapKey.insert(121, "F10");
    myMapKey.insert(122, "F11");myMapKey.insert(123, "F12");myMapKey.insert(144, "NumLock");
    myMapKey.insert(145, "ScrollLock");myMapKey.insert(154, "PrintScreen"); myMapKey.insert(157, "Meta");
    myMapKey.insert(186, ";");myMapKey.insert(187, "="); myMapKey.insert(188, ",");
    myMapKey.insert(189, "-");myMapKey.insert(190, "."); myMapKey.insert(191, "/");
    myMapKey.insert(192, "~");myMapKey.insert(219, "["); myMapKey.insert(220, "'\'");
    myMapKey.insert(221, "]"); myMapKey.insert(222, "'");
}

void Registration_Key::Recieve_data(int Row, QString keys)
{
    row = Row;
    ui->this_keys->setText(keys);
}

void Registration_Key::on_CloseApp_clicked()
{
    emit sendEnabler(true);

    delete Keys_event;
    this->close();
    delete this;
}

void Registration_Key::on_register_hothey_clicked()
{
    if(!flag_Apply){
        Messages * messages = new Messages;
        messages->set_Title_and_Text("Ошибка", "Назначьте другое сочетание клавиш!",  false, false);
        messages->show();
        return;
    }
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    if(row == 0){
        settings->setValue("HotKey_Play/id_One_Key", id_Key_One);
        settings->setValue("HotKey_Play/id_Two_Key", id_Key_two);
        settings->setValue("HotKey_Play/Key_Name", Key_One + " + " + Key_Two);
        settings->sync();
    }
    if(row == 1){
        settings->setValue("HotKey_Next/id_One_Key", id_Key_One);
        settings->setValue("HotKey_Next/id_Two_Key", id_Key_two);
        settings->setValue("HotKey_Next/Key_Name", Key_One + " + " + Key_Two);
        settings->sync();
    }
    if(row == 2){
        settings->setValue("HotKey_Previous/id_One_Key", id_Key_One);
        settings->setValue("HotKey_Previous/id_Two_Key", id_Key_two);
        settings->setValue("HotKey_Previous/Key_Name", Key_One + " + " + Key_Two);
        settings->sync();
    }
    if(row == 3){
        settings->setValue("HotKey_Add/id_One_Key", id_Key_One);
        settings->setValue("HotKey_Add/id_Two_Key", id_Key_two);
        settings->setValue("HotKey_Add/Key_Name", Key_One + " + " + Key_Two);
        settings->sync();
    }
    if(row == 4){
        settings->setValue("HotKey_Download/id_One_Key", id_Key_One);
        settings->setValue("HotKey_Download/id_Two_Key", id_Key_two);
        settings->setValue("HotKey_Download/Key_Name", Key_One + " + " + Key_Two);
        settings->sync();
    }
    if(row == 5){
        settings->setValue("HotKey_VolumeUp/id_One_Key", id_Key_One);
        settings->setValue("HotKey_VolumeUp/id_Two_Key", id_Key_two);
        settings->setValue("HotKey_VolumeUp/Key_Name", Key_One + " + " + Key_Two);
        settings->sync();
    }
    if(row == 6){
        settings->setValue("HotKey_VolumeDown/id_One_Key", id_Key_One);
        settings->setValue("HotKey_VolumeDown/id_Two_Key", id_Key_two);
        settings->setValue("HotKey_VolumeDown/Key_Name", Key_One + " + " + Key_Two);
        settings->sync();
    }
    emit sendEnabler(true);
    emit send_HotKey(Key_One, Key_Two, id_Key_One, id_Key_two, row);

    delete Keys_event;
    this->close();
    delete this;
}
