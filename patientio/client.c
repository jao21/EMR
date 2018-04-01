#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "menus.h"

int compareAccounts(User *userToCompare);
void adminMenu(User *userLoggedIn);
void doctorMenu(User *userLoggedIn);
void patientMenu(User *userLoggedIn);
void auditorMenu(User *userLoggedIn);

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
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Doc", 3) == 0)
			{
				doctorMenu(nUser);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Pat", 3) == 0)
			{
				patientMenu(nUser);
				free(nUser);
				return;
			}
			else if(strncmp(nUser->role, "Aud", 3) == 0)
			{
				auditorMenu(nUser);
				free(nUser);
				return;
			}
		}
		else
		{
			printf("Invalid Login!\n");
		}
		imp++;
		free(nUser);
	} while (imp < 3);

	printf("\n\nToo many failed login attempts. Error logged and Admin notified.\n\n");
}

int main()
{
	login();
	return 0;
}
