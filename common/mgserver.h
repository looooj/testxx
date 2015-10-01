//---------------------------------------------------------------------------

#ifndef MgServerH
#define MgServerH



#include <common/mongoose.h>
#include <common/mysleep.h>
#include <pthread.h>


typedef void (*mg_server_request_handler)(struct mg_connection* conn);


class MgServer
{
public:
    MgServer();
    virtual ~MgServer();
    bool start();
    bool open()
    {
        return start();
    }
    void close()
    {
        stop();
    }
    bool isStop();
    void setStop();

    void stop();
    void loop();
    
    void setBindIp(const char* ip);
    int getPort();
    void setPort(int port);
    int handler(struct mg_connection* conn, enum mg_event);
    
    void setRequestHandler(mg_server_request_handler handler)
    {
        this->mRequestHandler = handler;
    }
    
protected:
    mg_server_request_handler mRequestHandler;
    virtual void doRequest(struct mg_connection* conn);
private:
    
    int mStopFlag;
    int mPort;
    int mIndex;
    char mBindIp[256];
    struct mg_server* mServer;
    pthread_t mMainThread;
};





//---------------------------------------------------------------------------
#endif
