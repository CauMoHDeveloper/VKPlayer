#ifndef AUDIOEDIT_H
#define AUDIOEDIT_H

#include <QWidget>
#include "widgetparent.h"
#include "messages.h"

namespace Ui {
class AudioEdit;
}

class AudioEdit : public WidgetParent
{
    Q_OBJECT

public:
    explicit AudioEdit(WidgetParent *parent = 0);
    ~AudioEdit();

private slots:
    void on_SaveEdit_clicked();
    void on_CloseApp_clicked();

public slots:
    void recieve_data(QString audio_id, QString owner_id, QString Artist, QString Title,
                      QString genre, QString token);
    void GenreEdit(QString);
    void DrawGUI();

signals:
    void success_edit(QString, QString, QString);


private:
    Ui::AudioEdit *ui;

    QString audio_id_tmp;
    QString owner_id_tmp;
    QString Artist_tmp;
    QString Title_tmp;
    QString genre_tmp;
    QString token_tmp;
    QMap<int, QString> Genre;
    int flag;
};

#endif // AUDIOEDIT_H
