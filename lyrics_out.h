#ifndef LYRICS_OUT_H
#define LYRICS_OUT_H

#include <QWidget>
#include "widgetparent.h"
#include <QScrollBar>
#include <QLabel>
#include <QMovie>

namespace Ui {
class lyrics_out;
}

class lyrics_out : public WidgetParent
{
    Q_OBJECT

public:
    explicit lyrics_out(WidgetParent *parent = 0);
    ~lyrics_out();

public slots:
    void out_Text_Song(QString text);
    void DrawGUI();

signals:
    void complete_recieving();
    void close_lyrics(bool);

private slots:
    void on_CloseApp_clicked();

private:
    Ui::lyrics_out *ui;
    QLabel Loading;
};

#endif // LYRICS_OUT_H
