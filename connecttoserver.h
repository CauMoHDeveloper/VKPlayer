#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H
#include <QTcpSocket>
#include <QTime>
#include <QObject>
#include <QHostAddress>
#include <QFile>
#include <QTimer>

class ConnectToServer : public QObject
{
    Q_OBJECT
public:
    explicit ConnectToServer(QObject *parent = 0);
    ~ConnectToServer();
signals:

public slots:

private slots:
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   (                            );
    void slotReadyRead();
    void slotUpdateClient();
    void send_Download_music();

private:
    QTcpSocket* m_pTcpSocket;
    QTimer* ptimer;
    QString UserId;

};

#endif // CONNECTTOSERVER_H
