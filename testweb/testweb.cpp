#include <stdlib.h>

#include <common/timeutils.h>
#include <common/mgserver.h>
#include <common/exithandler.h>


void testWebHandler(struct mg_connection* conn)
{
    char t[256];
    
    mg_printf_data( conn, "%s [%s] %s\n", 
       conn->request_method, conn->uri, timeUtils::timeString(t) );
}
MgServer testServer;
int port=8830;
int runTestWeb()
{

    testServer.setPort(port);
    testServer.setRequestHandler(testWebHandler);
    testServer.start();
    
}

int main(int argc, char* argv[])
{

    if ( argc > 1 )
        port = atoi(argv[1]);
    runTestWeb();
    
    WaitExitLoop();
    
    return 0;    
}
