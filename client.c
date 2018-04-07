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
				const int catcher1 = logMessage(0);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Doc", 3) == 0)
			{
				doctorMenu(nUser);
				const int catcher2 = logMessage(2);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Pat", 3) == 0)
			{
				patientMenu(nUser);
				const int catcher3 = logMessage(3);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Aud", 3) == 0)
			{
				auditorMenu(nUser);
				const int catcher4 = logMessage(4);
				free(nUser);
				return;
			}
		}
		else
		{
			printf("Invalid Login!\n");
			const int catcher5 = logMessage(6);
		}
		imp++;
		free(nUser);
	} while (imp < 3);

	printf("\n\nToo many failed login attempts. Error logged and Admin notified.\n\n");
	const int catcher6 = logMessage(7);
	
}

int logMessage (int message) 
{
	FILE *f;
	f = fopen("logFile.txt", "a+");
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
		strncpy(messageT,c_time_string,156);
		strncpy(messageW," Successful login as Doctor ",50);
	}
	
	else if(message == 0)
	{
		strncpy(messageT,c_time_string, 156);
		strncpy(messageW," Successful login as Admin", 50);
	}
	
	else if(message == 3)
	{
		strncpy(messageT,c_time_string, 156);
		strncpy(messageW," Successful login as Patient ",50);
	}
	
	else if(message == 4)
	{
		strncpy(messageT,c_time_string, 156);
		strncpy(messageW," Successful login as Auditor ",50);
	}
	
	else if(message == 5)
	{
		strncpy(messageT,c_time_string,156);
		strncpy(messageW," This is a tester, please ignore. ",50);
	}
	
	else if(message == 6)
	{
		strncpy(messageT,c_time_string,156);
		strncpy(messageW," Invalid login ",50);
	}
	
	else if(message == 7)
	{
		strncpy(messageT,c_time_string,156);
		strncpy(messageW," Too many login attempts ",50);
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
	
	const int catcher1 = fputs(messageT, f);
	const int catcher2 = fputs(messageW, f);
	const int catcher3 = fputs("\n", f);	
	fclose(f);
	
	return 0;
}

int main()
{
	login();
	return 0;
}
