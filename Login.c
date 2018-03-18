#include <stdio.h>
#include <stdlib.h>

void compare_login(char entered_id[], char entered_pass[])
{
	FILE *fp;
	char id[30];
	char pass[30];
	char type[10];
	int success = 0;
	static const char admin = 'a';
	static const char doctor = 'd';
	static const char patient = 'p';
	static const char auditor = 'u';
	
	//open file in read only mode
	fp = fopen("test.txt", "r");
	
	//if file does not exist print error and close program
	if(fp == NULL)
	{
		puts("Error.  File does not exist");
		return (EXIT_FAILURE);
	}
	
	char buf[BUFSIZ] = "Garbage";

	//loop runs until it reaches the end of the file
	while(fgets(buf, sizeof(buf), fp) != NULL)
	{
		fscanf(fp, "%s %s %s", id, pass, type);  //scan username, password, and account type from the file

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
		scanf("%s", &id);
	
		printf("Please enter your password\n");
	
		scanf("%s", &pass);
		printf("\n");
		printf("Login: %s\n", &id);
		printf("Password: %s\n\n", &pass);
		
		compare_login(id, pass); 	
	}
}

int main()
{
	char id[30];
	char pass[30];
	
	printf("Please enter your username\n");
	scanf("%s", &id);

	printf("Please enter your password\n");

	scanf("%s", &pass);
	printf("\n");
	printf("Login: %s\n", &id);
	printf("Password: %s\n\n", &pass);
	
	compare_login(id, pass);    
	return 0;
}



