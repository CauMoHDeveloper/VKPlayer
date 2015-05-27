#include "labelnew.h"
#include <QPainter>
#include <QMovie>



LabelNew::LabelNew(QLabel *parent) :
    QLabel(parent)
{
}

void LabelNew::paintEvent(QPaintEvent *)
{
    /*QPainter p(this);
    p.setOpacity(0.8);*/
    update();
    QMovie *movie = new QMovie(":/new/prefix1/loading32.gif");
    this->setMovie(movie);
    movie->start();
}
