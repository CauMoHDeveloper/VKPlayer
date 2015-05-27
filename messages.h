#ifndef MESSAGES_H
#define MESSAGES_H

#include <QWidget>
#include "widgetparent.h"

namespace Ui {
class Messages;
}

class Messages : public WidgetParent
{
    Q_OBJECT

public:
    explicit Messages(WidgetParent *parent = 0);
    ~Messages();

public slots:
    void set_Title_and_Text(QString title, QString Text, bool Show_DB, bool Show_ReWrite);
    void DrawGUI();

private slots:
    void on_Ok_Button_clicked();
    void on_Download_Button_clicked();
    void on_CloseApp_clicked();
    void on_ReWrite_clicked();

signals:
    void click_ReWrite();
    void click_Ok();

private:
    Ui::Messages *ui;
};

#endif // MESSAGES_H
