#include "create_thread.h"

VkCreateThreade::VkCreateThreade()
{
    get = NULL;
}

VkCreateThreade::~VkCreateThreade()
{
    if (get != NULL) {
            delete get;
        }
}



void VkCreateThreade::process()
{
    get = new VkGet;
    ans = get->GET(url);
    emit finished(ans);
    connect(this,SIGNAL(finish()),this, SLOT(GET()));
    emit finish();
}

QByteArray VkCreateThreade::GET()
{
    return ans;
}

void VkCreateThreade::stop(){
    if(get != NULL)
    {
        delete get;
    }
    return ;
}
