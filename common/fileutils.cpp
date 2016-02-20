#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "autofileptr.h"
#include "fileutils.h"



int readFileLines(const char* fn, std::vector<std::string>& lines) 
{
        
    AutoFilePtr file( fn, "rb" );

    int total=0;
        
    FILE* fp = file.get();
    if ( fp )
    {
        
        while(1) {
            char line[4096];
            if ( feof(fp) )
                break;                
            if ( fgets( line, 4000, fp ) )
                lines.push_back( line );
            total++;
            
        }
    }    
    return total;    
}    
    
    
void writeFileLines(const char* fn, std::vector<std::string>& lines, int lineEnd) 
{
    
    AutoFilePtr file( fn, "wb" );
    
    if ( file.get() )
    {
        for(int i = 0; i < lines.size(); i++  ) {
         
            std::string& line = lines[i];
            file.write( line.c_str(), line.length() );
            if ( lineEnd == LINE_END_TWO )
                file.write( "\x0d\0x0a", 2 );    
            else
                file.write( "\0x0a", 1 );    
        }
          
    }    
}        
        

int readFileString(const char* fn, std::string& text) 
{
    
    AutoFilePtr file( fn, "rb" );

    int total=-1;
        
    if ( file.get() ) 
    {
        total = 0;
        while(1) {
            char line[4096];
            int r = file.read( line, 4000 );
            if ( r <= 0 ) 
                break;
            total += r;           
            text.append( line, r );
        }
    }    
    return total;
            
}

int writeStringToFile(const char* fn, std::string& text) 
{
        
    AutoFilePtr file( fn, "wb" );
    
    if ( file.get() )
        file.write( text.c_str(), text.length() );
        
}

int fileSize(const char* fn) 
{
    struct stat st;
    memset(&st, 0, sizeof(st) );
    stat(fn, &st); 
    return st.st_size;    
}

bool fileExists(const char* fn)
{
    if (0 == access(fn, 0))
        return true;
        
    return false;
}

    