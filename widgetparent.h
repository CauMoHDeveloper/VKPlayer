#ifndef WIDGETPARENT_H
#define WIDGETPARENT_H

#include <QWidget>

#include <QMouseEvent>
#include <QMap>
#include <QPropertyAnimation>
#include "vk_get.h"
#include <QUrl>
#include <QUrlQuery>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QSettings>

class WidgetParent : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetParent(QWidget *parent = 0);

    static const int kDropShadowSize;
    static const int kBorderRadius;

    static bool IsTransparencyAvailable();

public:
      QRect BoxBorder() const;
      QRgb background_color() const { return background_color_.rgb(); }
signals:

public slots:
    void setRoundedCorners(int radius_tl, int radius_tr, int radius_bl, int radius_br);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    QString Read_Stylesheet(QString);
    void setGeom(QString);
    void saveGeom(QString);

protected slots:


public:
    bool b_move;
    QPoint lastPoint;
    // Cached pixmaps
    QPixmap shadow_edge_[4];
    QPixmap shadow_corner_[4];
    QColor background_color_;
    QPixmap background_;
};

#endif // WIDGETPARENT_H
