#ifndef file_utils_h_xx
#define file_utils_h_xx



#include <string>
#include <vector>


#define LINE_END_ONE  1
#define LINE_END_TWO  2


int readFileLines(const char* fn, std::vector<std::string>& lines);
void writeFileLines(const char* fn, std::vector<std::string>& lines, int lineEnd=LINE_END_ONE);
    

int readFileString(const char* fn, std::string& text);
int writeStringToFile(const char* fn, std::string& text);


int fileSize(const char* fn);

bool fileExists(const char* fn);





#endif

