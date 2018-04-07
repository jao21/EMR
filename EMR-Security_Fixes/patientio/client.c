#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "users.h"
#include "menus.h"

int compareAccounts(User *userToCompare);
void adminMenu(User *userLoggedIn);
void doctorMenu(User *userLoggedIn);
void patientMenu(User *userLoggedIn);
void auditorMenu(User *userLoggedIn);
int logMessage(int message);
char messageT [156];
char messageW [50];
void login()
{
	int imp = 0;
	do
	{
		User *nUser = (User*)malloc(sizeof(User));
		
		if(NULL == nUser)
		{
			//may want better error handling here
			printf("Error");
			exit(0);
		}

		
		printf("Please enter your username\n");
		if(!(fgets(nUser->userName, 15, stdin)))
		{
			printf("I/O error");
			exit(0);
		}
		const size_t uLen = strlen(nUser->userName);
		if (uLen && (nUser->userName[uLen-1] == '\n'))
		{
			nUser->userName[uLen-1] = '\0';
		}
		
		printf("Please enter your password\n");

		if(!(fgets(nUser->password, 15, stdin)))
		{
			printf("I/O error");
			exit(0);
		}
		const size_t pLen = strlen(nUser->password);
		if (pLen && (nUser->password[pLen-1] == '\n'))
		{
			nUser->password[pLen-1] = '\0';
		}
		printf("\n");

		if(compareAccounts(nUser) == 0)  //compare user entered credentials to the current credentials in the file
		{
			printf("You're logged in as %s\n\n", nUser->name);
			if(strncmp(nUser->role, "Adm", 3) == 0)
			{
				adminMenu(nUser);
				logMessage(0);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Doc", 3) == 0)
			{
				doctorMenu(nUser);
				logMessage(2);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Pat", 3) == 0)
			{
				patientMenu(nUser);
				logMessage(3);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Aud", 3) == 0)
			{
				auditorMenu(nUser);
				logMessage(4);
				free(nUser);
				return;
			}
		}
		else
		{
			printf("Invalid Login!\n");
			logMessage(6);
		}
		imp++;
		free(nUser);
	} while (imp < 3);

	printf("\n\nToo many failed login attempts. Error logged and Admin notified.\n\n");
	logMessage(7);
	
}

int logMessage (int message) 
{
	FILE *f;
	f = fopen("logFile.txt", "a");
	if (!f)
	{
		printf("File I/O error.");
		return 1;
	}    
	
	time_t current_time;
    char* c_time_string;

    /* Obtain current time. */
    current_time = time(NULL);

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

	
	
	if(message == 2)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Successful login as Doctor ");
	}
	
	else if(message == 1)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," File I/O error.");
	}
	
	else if(message == 3)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Successful login as Patient ");
	}
	
	else if(message == 4)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Successful login as Auditor ");
	}
	
	else if(message == 5)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," This is a tester, please ignore. ");
	}
	
	else if(message == 6)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Invalid login ");
	}
	
	else if(message == 7)
	{
		strcpy(messageT,c_time_string);
		strcpy(messageW," Too many login attempts ");
	}
	
	/*if (strcpy(messageT) == EOF) 
	{
		printf("File I/O Error")
		return 1;
	}
	if (strcpy(messageW) == EOF) 
	{
		printf("File I/O Error")
		return 1;
	}*/
	
	fputs(messageT, f);
	fputs(messageW, f);
	fputs("\n", f);	
	fclose(f);
	
	return 0;
}

int main()
{
	login();
	return 0;
}
