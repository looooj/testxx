#ifndef auto_file_ptr_h_xx
#define auto_file_ptr_h_xx


#include <stdio.h>


class AutoFilePtr
{

FILE* fp;


public:
    
    AutoFilePtr() 
    {
        fp = 0;        
    }
    
    AutoFilePtr(const char* fn, const char* flags) 
    {
        fp = 0;
        open(fn,flags);
    }    
    
    ~AutoFilePtr()
    {
        close();
    }
    
    bool open(const char* fn, const char* flags) 
    {
        fp = fopen( fn, flags );
        
        return fp != 0;
    }
    
    int read(void* buf, int count)
    {
        int r = 0;
        if ( fp )
           r = fread( buf, 1, count, fp );
        
        return r;
    }
    
    int write(const void* buf, int count)
    {
        int r = 0;
        if ( fp )
           r = fwrite( buf, 1, count, fp );
        
        return r;
    }
    
    void close() 
    {
        if ( fp )
            fclose(fp);
        fp = 0;
    }
    
    
    FILE* get() 
    {
        return fp;
    }
    
};








#endif
