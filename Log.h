#ifndef LOG_H
#define LOG_H
#include <time.h>

int message = 0;
char messageT [156];
char messageW [50];
time_t current_time;
char* c_time_string;

int logMessage (int message);


#endif
