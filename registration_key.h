#ifndef REGISTRATION_KEY_H
#define REGISTRATION_KEY_H

#include <QWidget>
#include "widgetparent.h"
#include "messages.h"

namespace Ui {
class Registration_Key;
}

class Registration_Key : public WidgetParent
{
    Q_OBJECT

public:
    explicit Registration_Key(WidgetParent *parent = 0);
    ~Registration_Key();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void DrawGUI();
    void filling_hotkey();
    void Recieve_data(int Row, QString keys);

private slots:
    void on_CloseApp_clicked();
    void on_register_hothey_clicked();

signals:
    void send_HotKey(QString, QString, int, int, int);
    void sendEnabler(bool);

private:
    Ui::Registration_Key *ui;
    QSet<int> * Keys_event;
    QString Key_One;
    QString Key_Two;
    int id_Key_One;
    int id_Key_two;
    int row;
    QHash<int, QString> myMapKey;
    bool flag_Key_One_true, flag_Key_Two_true, flag_Apply;
};

#endif // REGISTRATION_KEY_H
