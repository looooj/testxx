#include <string.h>

#include "mgserver.h"



void* MgServerThread(void* arg)
{
    if ( arg )
    {
        ((MgServer*)arg)->loop();
    }
}


int MgServerHandler(struct mg_connection* conn, enum mg_event evt)
{
    if ( conn->server_param )
    {
        return ((MgServer*)conn->server_param)->handler( conn, evt );
    }
    return MG_FALSE;
}

MgServer::MgServer()
{
    mMainThread = 0;
    mPort = 8080;
    mStopFlag = 0;
    strcpy( mBindIp, "0.0.0.0" );
}

MgServer::~MgServer()
{
}

int MgServer::getPort()
{
    return mPort;
}

void MgServer::setPort(int port)
{
    mPort = port;
}

void MgServer::setBindIp(const char* ip)
{
    strcpy( mBindIp, ip );
}    

void MgServer::loop()
{
    while(1)
    {
        if ( mStopFlag )
            break;
        mg_poll_server(mServer, 1000);
        Sleep(1);
    }
    mg_destroy_server(&mServer);
    mServer = 0;

}

bool MgServer::start()
{
    mStopFlag = 0;

    struct mg_server *server = mg_create_server(this, MgServerHandler);
    mg_set_option(server, "document_root", ".");

    char tmp_port[16];
    sprintf( tmp_port, "%s:%d", mBindIp, mPort );
    const char* result =  mg_set_option(server, "listening_port",  tmp_port );

    if ( result != NULL )
        return false;
        
    mServer = server;

    pthread_create( &mMainThread, NULL, MgServerThread, this ); 

    return true;
}

void MgServer::stop()
{
    mStopFlag = 1;
    pthread_join( mMainThread, NULL );
}

void MgServer::setStop()
{
    mStopFlag = 1;
}

bool MgServer::isStop()
{
    //if ( !mMainThread )
    //    return !mMainThread->IsRun();
    return false;
}

int MgServer::handler(struct mg_connection* conn, enum mg_event evt)
{

    if (evt == MG_AUTH)
    {
        return MG_TRUE;
    }
    else
    if (evt == MG_REQUEST )
    {

        doRequest(conn);
        //mg_printf_data(conn, "%s", "Hello");
        return MG_TRUE;
    }
    else
    {
        return MG_FALSE;  // Rest of the events are not processed
    }

}

void MgServer::doRequest(struct mg_connection* conn)
{
    if ( mRequestHandler )
        mRequestHandler(conn);


}


//---------------------------------------------------------------------------

