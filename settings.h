#ifndef SETTINGS_H
#define SETTINGS_H
#include "widgetparent.h"
#include <QWidget>
#include "registration_key.h"
#include <QTableWidgetItem>

namespace Ui {
class Settings;
}

class Settings : public WidgetParent
{
    Q_OBJECT

public:
    explicit Settings(WidgetParent *parent = 0);
    ~Settings();

signals:
    void valueR(int R);
    void valueG(int G);
    void valueB(int B);
    void standartC();
    void cls();
    void sEnabled(bool);
    void Transpar(int v);
    void exit_ACC();
    void Directory(QString directory);
    void StartDownloadNewVersion();
    void ChangeSpeedText(int);
    void ChangeNotification(bool);
    void ChangeHideToTray(bool);
    void send_new_hotkey(int, int, int);

public slots:
    void sendValueR(int R);
    void sendValueG(int G);
    void sendValueB(int B);
    void sendTransparency(int value);
    void MenuChooseDirectory();
    void DrawGUI();
    void printNewVersion(bool val);
    void printErrorUpdating(bool val);
    void DownloadSettings();
    void Save_SpeedSOngText(int);
    void selectedItem(QTableWidgetItem*);
    void apply_new_HotKey(QString, QString, int, int, int);

protected:
    bool eventFilter(QObject* watched, QEvent* event);

private slots:
    void on_StandartColor_clicked();
    void on_CloseApp_clicked();
    void on_Random_Color_clicked();
    void on_Exit_account_clicked();
    void on_Download_Dir_BTN_clicked();
    void on_Open_Site_BTN_clicked();
    void on_CheckNewVER_clicked();
    void on_UpdateOLD_clicked();
    void on_Default_HotKey_clicked();

private:
    Ui::Settings *ui;
    int r, g, b, valupdate;
    float tran;
};

#endif // SETTINGS_H









