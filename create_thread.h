#ifndef CREATE_THREAD_H
#define CREATE_THREAD_H
#include "widget.h"

class VkCreateThreade : public QObject
{
    Q_OBJECT
public:
    VkCreateThreade();
    ~VkCreateThreade();

    void translate_data(const QUrl &Url) {url = Url;}

public slots:
    void stop();
    void process();
    QByteArray GET();


signals:
    void finished(QByteArray ans);
    void finish();

private:
    class VkGet * get;
    QUrl url;
    QByteArray ans;
};
#endif // CREATE_THREAD_H
