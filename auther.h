#ifndef AUTHER_H
#define AUTHER_H

#include <QWidget>

#include "widgetparent.h"


namespace Ui {
class auther;
}

class auther : public WidgetParent
{
    Q_OBJECT

public:
    explicit auther(WidgetParent *parent = 0);
    ~auther();

private slots:
    void on_CloseApp_clicked();
    void on_hideApp_clicked();

public slots:
    void print_auth_erroR(bool val);
    void run_player(QString token, QString Id);
    void chech_auth();
    void DownloadSettings();
    void DrawGUI();

private:
    Ui::auther *ui;
    class helloy * Hell;
    class VkAuth *auth;
    int R, G, B;
    float TR;
};

#endif // AUTHER_H
