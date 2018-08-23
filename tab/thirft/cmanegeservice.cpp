#include "cmanegeservice.h"



CManegeService::CManegeService()
{

}

void CManegeService::setOpenPort()
{

}

void CManegeService::getOpenPort(int &intPort)
{

}

void CManegeService::startService()
{
    if (!m_pThreadHandle)
    {
        m_pThreadHandle = boost::make_shared<boost::thread>(boost::bind(&CCollectLoadService::CollectLoadProc, this));
    }
}

void CManegeService::stopService()
{
    if (m_pThreadHandle){
    try
        {
            if (s_pPoolServer)
            {
                s_pPoolServer->stop();
            }

        }
        catch (TException& e)
        {
            //ERROR_LOG("call [%s] when stop receive node heartbeat a exception,the exception is [%s].", __FUNCTION__,e.what());
        }
        //等待线程结束
        m_pThreadHandle->join();
    }
}

void CManegeService::prepareService()
{
    int port = 27020;

    boost::shared_ptr<ConcreteCollectLoadHandler> handler(new ConcreteCollectLoadHandler());
    boost::shared_ptr<TProcessor> processor(new ReportNodeLoadInfoProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(m_nOpenPort));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    //支持管理100个节点
    int nConCurrecncy = 100;//boost::thread::hardware_concurrency();
    boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(nConCurrecncy);
    threadManager->threadFactory(boost::make_shared<PlatformThreadFactory>());
    threadManager->start();
    s_pPoolServer = boost::make_shared<TThreadPoolServer>(processor, serverTransport, transportFactory, protocolFactory, threadManager);
    if (s_pPoolServer)
    {
        s_pPoolServer->serve();
    }
}
