#include <stdio.h>
#include <stdlib.h>

void compare_login(char entered_id[], char entered_pass[])
{
	FILE *fp;
	char id[30];
	char pass[30];
	char type[10];
	int success = 0;
	static const unsigned char admin = 'a';
	static const unsigned char doctor = 'd';
	static const unsigned char patient = 'p';
	static const unsigned char auditor = 'u';
	
	//open file in read only mode
	fp = fopen("test.txt", "r");
	
	//if file does not exist print error and close program
	if(fp == NULL)
	{
		printf("Error.  File does not exist");
		exit(1);
	}
	
	char buf[] = "Garbage";

	//loop runs until it reaches the end of the file
	while(fgets(buf, sizeof(buf), fp) != NULL)
	{
		fscanf_s(fp, "%s %s %s", id, sizeof(id), pass, sizeof(pass), type, sizeof(type));  //scan username, password, and account type from the file

		if(strcmp(entered_id, id) == 0 && strcmp(entered_pass, pass) ==0)  //compare user entered credentials to the current credentials in the file
		{
			printf("You're logged in as %s\n\n", entered_id);
			//set success to match appropriate account type
			if(*type == admin)
				success = 1;
			else if(*type == doctor)
				success = 2;
			else if(*type == patient)
				success = 3;
			else if(*type == auditor)
				success = 4;
		}
	}
	//print next appropriate menu based on the account type.  Code needs to be written for these menus
	if(success == 1)
		printf("Admin Menu");
	else if(success == 2)
		printf("Doctor Menu");
	else if(success == 3)
		printf("Patient Menu");
	else if(success == 4)
		printf("Auditor Menu");
	else
	{
		printf("Invalid Login!\n"); 
		printf("Please enter your username\n");
		if(scanf_s("%s", &id, sizeof(id)) == EOF)
		{
			printf("I/O error");
			exit(0);
		}
	
		printf("Please enter your password\n");
	
		if(scanf_s("%s", &pass, sizeof(pass)) == EOF)
		{
			printf("I/O error");
			exit(0);
		}
		printf("\n");
		printf("Login: %s\n", &id);
		printf("Password: %s\n\n", &pass);
		
		compare_login(id, pass); 	
	}
	
	fclose(fp);
}

int main()
{
	char id[30];
	char pass[30];
	
	printf("Please enter your username\n");
	if(scanf_s("%s", &id, sizeof(id)) == EOF)
	{
		printf("I/O error");
		exit(0);
	}

	printf("Please enter your password\n");

	if(scanf_s("%s", &pass, sizeof(pass)) == EOF)
	{
		printf("I/O error");
		exit(0);
	}
	printf("\n");
	printf("Login: %s\n", &id);
	printf("Password: %s\n\n", &pass);
	
	compare_login(id, pass);    
	return 0;
}



