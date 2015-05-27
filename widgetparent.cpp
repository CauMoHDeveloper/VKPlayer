//Переопределнный класс QWidget
//Используется всеми окнами в программе

#include "widgetparent.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QLayout>
#include <QSettings>
#include <QMouseEvent>
#include <QTimer>
#include <QBitmap>
#include <QTimeLine>

#ifdef Q_WS_X11
#  include <QX11Info>
#endif

#ifdef Q_OS_WIN32
#  include "qtwin.h"
#endif

const int WidgetParent::kDropShadowSize = 1;
const int WidgetParent::kBorderRadius = 3;


WidgetParent::WidgetParent(QWidget *parent) :
    QWidget(parent)
{        
    // Load the show edges and corners
    QImage shadow_edge(":/background/osd_shadow_edge.png");
    QImage shadow_corner(":/background/osd_shadow_corner.png");
    for (int i=0 ; i<4 ; ++i) {
      QTransform rotation = QTransform().rotate(90 * i);
      shadow_edge_[i] = QPixmap::fromImage(shadow_edge.transformed(rotation));
      shadow_corner_[i] = QPixmap::fromImage(shadow_corner.transformed(rotation));
    }
    background_ = QPixmap(":/background/osd_background.png");
}

QRect WidgetParent::BoxBorder() const {
  return rect().adjusted(kDropShadowSize, kDropShadowSize,
                         -kDropShadowSize, -kDropShadowSize);
}

bool WidgetParent::IsTransparencyAvailable() {
#ifdef Q_WS_X11
  return QX11Info::isCompositingManagerRunning();
#endif
  return true;
}

void WidgetParent::paintEvent(QPaintEvent *)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  p.setRenderHint(QPainter::HighQualityAntialiasing);

  QRect box(BoxBorder());

  // Shadow edges
  const int kShadowCornerSize = kDropShadowSize + kBorderRadius;
  p.drawTiledPixmap(kShadowCornerSize, 0,
                    width() - kShadowCornerSize*2, kDropShadowSize,
                    shadow_edge_[0]);
  p.drawTiledPixmap(width() - kDropShadowSize, kShadowCornerSize,
                    kDropShadowSize, height() - kShadowCornerSize*2,
                    shadow_edge_[1]);
  p.drawTiledPixmap(kShadowCornerSize, height() - kDropShadowSize,
                    width() - kShadowCornerSize*2, kDropShadowSize,
                    shadow_edge_[2]);
  p.drawTiledPixmap(0, kShadowCornerSize,
                    kDropShadowSize, height() - kShadowCornerSize*2,
                    shadow_edge_[3]);

  // Background pattern
  QPainterPath background_path;
  background_path.addRoundedRect(box, kBorderRadius, kBorderRadius);
  p.setClipPath(background_path);
  p.setOpacity(0.55);
  p.drawPixmap(box.right() - background_.width(),
               box.bottom() - background_.height() - 450, background_);
  p.setClipping(false);

  // Gradient overlay
  QLinearGradient gradient(0, 0, 0, height());
  gradient.setColorAt(0, QColor(255, 255, 255, 70));
  gradient.setColorAt(1, QColor(255, 255, 255, 8));
  p.setBrush(gradient);
  p.drawRoundedRect(box, kBorderRadius, kBorderRadius);


  // Box borde
  p.setBrush(QBrush());
  p.setPen(QPen(QColor()));
  p.drawRoundedRect(box, kBorderRadius, kBorderRadius);

}

void WidgetParent::setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br)
{

    QBitmap mask(size());
    mask.clear();

    QPainter p(&mask);
    p.setBrush(Qt::color1);
    p.drawRoundedRect(BoxBorder().adjusted(-1, -1, 0, 0), kBorderRadius, kBorderRadius);
    p.end();

    setMask(mask);

}

void WidgetParent::mousePressEvent(QMouseEvent *event)              //Обработка перемещения окна. Нажатие на окно
{
    //QRect p = this->geometry();
    if(event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        b_move = true;
    }
}

void WidgetParent::mouseMoveEvent(QMouseEvent *event)               //Обработка перемещения окна. Движение мыши
{
    if((event->buttons() & Qt::LeftButton) && b_move)
        move(event->globalX()-lastPoint.x()-10,
             event->globalY()-lastPoint.y()-30);
}

void WidgetParent::mouseReleaseEvent(QMouseEvent *event)            //Обработка перемещения окна. Отжатие кнопки мыши.
{
    if (event->button() == Qt::LeftButton && b_move) {
            b_move = false;
    }
}

QString WidgetParent::Read_Stylesheet(QString tmp)
{
    QFile file(tmp);
        QByteArray data;
        if (file.open(QIODevice::ReadOnly))
            data = file.readAll();

        return QString(data);
}

void WidgetParent::setGeom(QString obj)
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    if(!settings->value(obj + "/x").isNull()){
        int x = settings->value(obj + "/x").toInt();
        int y = settings->value(obj + "/y").toInt();
        int width = this->geometry().width();
        int height = this->geometry().height();
        QDesktopWidget *d = QApplication::desktop();
        int desktop_width = d->width();
        int desktop_height = d->height();
        qDebug()<<desktop_height << desktop_width << y << x;
        if(!(x < -283) && !(x > desktop_width) && !(y < 0) && !(y > desktop_height))
            this->setGeometry(x, y, width, height);
    }    
}

void WidgetParent::saveGeom(QString obj)
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    if(this->geometry().x() != 0 && this->geometry().y() != 0){
        settings->setValue(obj + "/x", this->geometry().x());
        settings->setValue(obj + "/y", this->geometry().y());
        settings->sync();
    }
}


