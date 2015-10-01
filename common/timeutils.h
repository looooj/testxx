#ifndef time_utils_h_xx
#define time_utils_h_xx


#include <sys/time.h>
#include <time.h>
#include <stdio.h>


#ifndef timeStruct

typedef struct
{
	  int year;
	  int month;
	  int day;
	  int minute;
	  int hour;
	  int second;
	  int milliseconds;	
} timeStruct;    

#endif


//struct tm *localtime_r(const time_t *timep, struct tm *result);

class timeUtils 
{

public:
    
    static char* timeString(char* s) 
    {
        //char s[256];
        timeStruct ts;
        
        getTime(&ts);
        
        sprintf( s, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
           ts.year,ts.month,ts.day,
           ts.hour, ts.minute, ts.second, ts.milliseconds );
           
        return s;
    }
    

    static timeStruct* getTime(timeStruct* ts) 
    {
    	struct timeval tv;
        struct timezone tz;
        gettimeofday (&tv , &tz);    	  
        
        ts->milliseconds = tv.tv_usec / 1000;

        struct tm* p;
        struct tm t;        
        p = localtime_r(&tv.tv_sec, &t);
            	
        ts->year = 1900 + p->tm_year;
        ts->month = p->tm_mon + 1;
        ts->day = p->tm_mday;
        ts->hour = p->tm_hour;
        ts->minute = p->tm_min;
        ts->second = p->tm_sec;        
        return ts;
    }


    
};






#endif



