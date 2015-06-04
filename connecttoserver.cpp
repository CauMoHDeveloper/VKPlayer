#include "connecttoserver.h"
#include <QSettings>
#include <QMessageBox>

//Данный класс имеет подключение с сервером статистики.
//Каждый 15 отправляет id пользователя вконтакте на этот сервер
//Работает в отдельном потоке

ConnectToServer::ConnectToServer(QObject *parent) :
    QObject(parent)
{
    m_pTcpSocket = new QTcpSocket();

    ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), this, SLOT(slotUpdateClient()));

    m_pTcpSocket->connectToHost("caumoh.dlinkddns.com",90);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError)));


    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    UserId = settings->value("TokenAndId/Id").toString();
qDebug("fsd");
    ptimer->start(900000);
}

ConnectToServer::~ConnectToServer()
{
    delete ptimer;
    delete m_pTcpSocket;
}

void ConnectToServer::slotError(QAbstractSocket::SocketError err)
{
    qDebug()<<err;
}

void ConnectToServer::slotConnected()
{
    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
    //QString version = settings->value("About/Version").toString();

     qDebug()<<"Connection...";
     m_pTcpSocket->write(UserId.toUtf8() + "  v."+/*version.toUtf8()*/"3.0 beta 1"+" WIN");
     qDebug()<<"Send UserId";
}

void ConnectToServer::slotReadyRead()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QByteArray Tmp = clientSocket->readAll();
    QString tmp = Tmp;
    QMessageBox msgBox;
    msgBox.setText(tmp);
    msgBox.setWindowTitle("Уведомление");
    msgBox.exec();
}

void ConnectToServer::slotUpdateClient()
{
    if(m_pTcpSocket->state() == QAbstractSocket::ConnectedState){
        QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);
        QString version = settings->value("About/Version").toString();

        m_pTcpSocket->write(UserId.toUtf8() + "  v."+version.toUtf8()+" WIN");
        qDebug()<<"Send UserId";
    }
    else{
        m_pTcpSocket->connectToHost("caumoh.dlinkddns.com",90);
    }
}

void ConnectToServer::send_Download_music()
{
    m_pTcpSocket->write("DOWNLOAD_MUSIC " + UserId.toUtf8());
}
