#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Log.h"

/*int main()
{
	logMessage(5);
	logMessage(5);

   return(0);
}*/

int logMessage (int message) 
{
	FILE *f;
	f = fopen("logFile.txt", "a");
	if (!f)
	{
		printf("File I/O errror.");
		return 1;
	}
        
	
	time_t current_time;
    char* c_time_string;

    /* Obtain current time. */
    current_time = time(NULL);

    /*if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
        exit(EXIT_FAILURE);
    }*/

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    /*if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.\n");
        exit(EXIT_FAILURE);
    }*/

    /* Print to stdout. ctime() has already added a terminating newline character. 
    (void) printf("Current time is %s", c_time_string);
    exit(EXIT_SUCCESS);*/
	

	
	if(message == 0)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Successful login as Admin ");
	}
	
	if(message == 2)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Successful login as Doctor ");
	}
	
	if(message == 3)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Successful login as Patient ");
	}
	
	if(message == 4)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Successful login as Auditor ");
	}
	
	if(message == 5)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," This is a tester, please ignore. ");
	}
	
	if(message == 6)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Invalid login ");
	}
	
	if(message == 6)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Too many login attempts ");
	}
	
	if (strcpy(messageT) == EOF) 
	{
		printf("File I/O Error")
		return 1;
	}
	if (strcpy(messageW) == EOF) 
	{
		printf("File I/O Error")
		return 1;
	}
	
	fputs(messageT, f);
	fputs(messageW, f);	
	fclose(f);
	
	return 0;
}

