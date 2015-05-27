#include "widget.h"
#include <QApplication>
#include "auther.h"
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication::setDesktopSettingsAware(false);   //Выключить управление шрифтами и стилями ОС
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Music Player");
    a.setApplicationName("VKPlayer");
    a.setApplicationVersion("2.2.1");
    a.setOrganizationName("CauMoH");
    a.setOrganizationDomain("CauMoH");

    a.setQuitOnLastWindowClosed(false);

    QFont monospace("MS Shell Dlg 2",8);
    monospace.setStyleStrategy(QFont::PreferAntialias);
    a.setFont(monospace);
    auther s;    
    s.chech_auth();
    return a.exec();
}
