#ifndef CMANEGESERVICE_H
#define CMANEGESERVICE_H

#include "tab/thirft/RPCMasterService_server.h"
boost::shared_ptr<TThreadPoolServer> s_pPoolServer;

class CManegeService
{
public:
    CManegeService();

public:
    void setOpenPort();

    void getOpenPort(int &intPort);

    void startService();

    void stopService();

private:
    void prepareService();

private:
    //服务的线程对象
    boost::shared_ptr<boost::thread> m_pThreadHandle;

};

#endif // CMANEGESERVICE_H
