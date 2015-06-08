#include "updateversion.h"
#include <QSettings>
#include "messages.h"

//Класс имеет подключение к серверу обновления
//Может проверять наличие новой версии ( испускает сигнал есть или нет )
//Может скачивать новую версию( испускает сигнал о удачном скачивании)


UpdateVersion::UpdateVersion(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    progress = new QProgressDialog();
    connect(this, SIGNAL(complete()), this, SLOT(checkNew()));
    Stop_update = false;
}

void UpdateVersion::dataReadProgress(qint64 done, qint64 total)        //Вывод прогресса загрузки
{
    progress->setMaximum(total);
    progress->setValue(done);
}

void UpdateVersion::checkNew()                                       //Проверить доступная новая версия или нет
{
    int OldValVersion = 0, NewValVersion = 0;

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    OldValVersion = settings->value("About/Version").toInt();
    NewValVersion = settings->value("UpdateVersion/Version").toInt();

    if(NewValVersion > OldValVersion)
    {
        emit NewVersionFound(true);
    }
    else
        emit NewVersionFound(false);
}

void UpdateVersion::StartCheck()                                     //Загрузка файла checkversion.txt
{
    flag = 1;
    url = "http://playervk.ru/checkversion.txt";
    this->downloader();
}

void UpdateVersion::StartUpdate()                                    //Старт скачки vkplayeract.exe
{
    messagesStartUpdate = new Messages;
    messagesStartUpdate->set_Title_and_Text("Обновление", "Идет обновление...", false, false);
    messagesStartUpdate->show();

    QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

    version = settings->value("UpdateVersion/Version").toString();
    url = settings->value("UpdateVersion/Url").toString();
    flag = 2;
    this->downloader();
}

void UpdateVersion::downloader()                                     //Метод для закачки файлов
{
    QNetworkReply * reply = manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
                    this, SLOT(dataReadProgress(qint64, qint64)));

    connect(this, SIGNAL(complete()), reply, SLOT(deleteLater()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(error_Reply(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(error_Ssl(QList<QSslError>)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    if(flag != 1)
    {
        progress->setLabelText("Загрузка обновления...");
        progress->show();
    }
}

void UpdateVersion::replyFinished (QNetworkReply *reply)             //Запись во временный файл
{
    try
    {
        if(reply->error())
    {
        qDebug() << reply->errorString();
        emit ErrorSignal(false);
    }
    else
    {
            try
            {

                if(progress != NULL)
                    progress->close();
            }
            catch(QException)
            {
            }

       if(flag == 2 && !Stop_update)
       {
           try
           {
               if(messagesStartUpdate != NULL && messagesStartUpdate->isVisible())
                   messagesStartUpdate->close();

           }
           catch(QException e)
           {
               qDebug()<<e.what();
           }

           QString tmpNameFile = "vkplayertemp.exe";

           QFile file(tmpNameFile);

             if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                 file.write("");
             file.close();

                 if(file.open(QFile::Append))
                 {
                     file.write(reply->readAll());
                     file.flush();
                     file.close();

                    /* QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

                     settings->setValue("About/Version", version);
                     settings->sync();*/

                     emit Restarting();
                 }

       }
       if(flag == 1 && !Stop_update)
       {
           QString str = reply->readAll();
           QStringList lst = str.split(" ");
           version = lst.at(0);
           url =  lst.at(1);

           QSettings * settings = new QSettings("settings.conf",QSettings::IniFormat);

           settings->setValue("UpdateVersion/Version", version);
           settings->setValue("UpdateVersion/Url", url);
           settings->sync();
           emit complete();
       }
    }
    }
    catch(QException e)
    {
        Messages * messages = new Messages;
        QString title, text;
        title = "Ошибка обновления";
        text = e.what();
        messages->show();
    }
 }

void UpdateVersion::error_Reply(QNetworkReply::NetworkError error)
{
    Messages * messages = new Messages;
    QString title, text;
    title = "Ошибка обновления";

    switch(error){

    case QNetworkReply::ConnectionRefusedError:
        text = "the remote server refused the connection (the server is not accepting requests).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::RemoteHostClosedError:
        text = "the remote server closed the connection prematurely, before the entire reply was received and processed.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::HostNotFoundError:
        text = "the remote host name was not found (invalid hostname).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::TimeoutError:
        text = "the connection to the remote server timed out.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::OperationCanceledError:
        text = "the operation was canceled via calls to abort() or close() before it was finished..";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::SslHandshakeFailedError:
        text = "the SSL/TLS handshake failed and the encrypted channel could not be established. The sslErrors() signal should have been emitted..";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::TemporaryNetworkFailureError:
        text = "the connection was broken due to disconnection from the network, however the system has initiated roaming to another access point. The request should be resubmitted and will be processed as soon as the connection is re-established..";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::NetworkSessionFailedError:
        text = "the connection was broken due to disconnection from the network or failure to start the network..";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::BackgroundRequestNotAllowedError:
        text = "the background request is not currently allowed due to platform policy..";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProxyConnectionRefusedError:
        text = "the connection to the proxy server was refused (the proxy server is not accepting requests).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProxyConnectionClosedError:
        text = "the proxy server closed the connection prematurely, before the entire reply was received and processed.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProxyNotFoundError:
        text = "the proxy host name was not found (invalid proxy hostname).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProxyTimeoutError:
        text = "the connection to the proxy timed out or the proxy did not reply in time to the request sent.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProxyAuthenticationRequiredError:
        text = "the proxy requires authentication in order to honour the request but did not accept any credentials offered (if any).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ContentAccessDenied:
        text = "the access to the remote content was denied (similar to HTTP error 401).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ContentOperationNotPermittedError:
        text = "the operation requested on the remote content is not permitted.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ContentNotFoundError:
        text = "the remote content was not found at the server (similar to HTTP error 404).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::AuthenticationRequiredError:
        text = "the remote server requires authentication to serve the content but the credentials provided were not accepted (if any).";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ContentReSendError:
        text = "the request needed to be sent again, but this failed for example because the upload data could not be read a second time.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProtocolUnknownError:
        text = "the Network Access API cannot honor the request because the protocol is not known.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProtocolInvalidOperationError:
        text = "the requested operation is invalid for this protocol";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::UnknownNetworkError:
        text = "an unknown error related to the remote content was detected";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::ProtocolFailure:
        text = "a breakdown in protocol was detected (parsing error, invalid or unexpected responses, etc.)";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    case QNetworkReply::UnknownContentError:
        text = "the operation requested on the remote content is not permitted.";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;

    default:
        text = "Other Error";
        messages->set_Title_and_Text(title, text, false, false);
        messages->show();
        break;
    }
    Stop_update = true;
}

void UpdateVersion::error_Ssl(QList<QSslError>)
{
    Messages * messages = new Messages;
    QString title, text;
    title = "Ошибка обновления";
    text = "Error SSL";
    messages->set_Title_and_Text(title, text, false, false);
    messages->show();
    Stop_update = true;
}
