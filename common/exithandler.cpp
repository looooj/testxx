#include <signal.h>
#include <unistd.h>

#include "exithandler.h"

int ExitFlag=0;
int ExitSignal=0;



void DefaultExitHandler(int s)
{
    ExitSignal = s;
    ExitFlag = 1;
}

void SetExitHandler()
{
    signal( SIGTERM, DefaultExitHandler );
    signal( SIGQUIT, DefaultExitHandler );
    signal( SIGPWR, DefaultExitHandler );
    signal( SIGINT, DefaultExitHandler );
    
}

void SetExitHandler(sighandler_t func)
{
    signal( SIGTERM, func );
    signal( SIGQUIT, func );
    signal( SIGPWR, func );
    signal( SIGINT, func );
    
}


void WaitExitLoop()
{
    SetExitHandler();
    
    while( true ) {
    
        if ( ExitFlag )
           break;
        usleep( 1000 * 1000 );
    }    
     
}