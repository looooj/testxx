#include <unistd.h>


void msleep(int ms)
{
    if ( ms < 1 )
    {
        usleep(1);
        return;
    }
    
    if ( ms < 1000 )
    {
        usleep( ms * 1000 );
        return;
    }
    
    sleep( ms / 1000 );
    
    ms = ms % 1000;
    
    usleep( ms );     
    
}
