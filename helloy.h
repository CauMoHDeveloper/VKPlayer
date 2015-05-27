#ifndef HELLOY_H
#define HELLOY_H

#include <QWidget>
#include "widgetparent.h"

namespace Ui {
class helloy;
}

class helloy : public WidgetParent
{
    Q_OBJECT

public:
    explicit helloy(WidgetParent *parent = 0);
    ~helloy();

private:
    Ui::helloy *ui;
};

#endif // HELLOY_H
