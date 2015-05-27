#ifndef LABELNEW_H
#define LABELNEW_H

#include <QLabel>

class LabelNew : public QLabel
{
    Q_OBJECT
public:
    explicit LabelNew(QLabel *parent = 0);

signals:

public slots:

protected:
 void paintEvent(QPaintEvent *);

};

#endif // LABELNEW_H
