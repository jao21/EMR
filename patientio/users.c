#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "users.h"
#include "fileio.h"

#define MAX_USERS 100

int OpenFile(FILE** file, char *fileName);
void CreateUserInfo(User *newUser);
int LookUpUser(FILE** file, User *userToLookUp, User *existingUser);
void UpdateAccounts(int updateUser, FILE** file, User *newUser, User *existingUser);
int AddUserToFile(FILE** file, User *newUser);
void UpdateUsersFile(FILE** file, User *newUser, int recPosition);
int displayAllUsers(FILE** file);
void GetUserAtPosition(FILE **file, int id, User *retrievedUser);
void fillUserTable(FILE** file, User *userTable, int size);
void RewriteUsersFile(FILE** file, User *userTable, int size, User *userToRemove);
void getUserByName(FILE** file, char *name, User *retrievedUser);
void clearInteger(int num);

/* Menu option to add a user account */
void addUserAccount()
{
  FILE *userF;
  User *userP = (User*)malloc(sizeof(User));
  
    if(NULL == userP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&userF, "users.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  CreateUserInfo(userP);

  User *exUserP = (User*)malloc(sizeof(User));
  
    if(NULL == exUserP)
	{
		printf("Error");
		exit(0);
	}
	
  const int updateUser = LookUpUser(&userF, userP, exUserP);

  UpdateAccounts(updateUser, &userF, userP, exUserP);
  fclose(userF);
  free(userP);
  userP = NULL;
  free(exUserP);
}

/* Menu option to update an existing user account */
void updateUserAccount()
{
  FILE *userF;
  User *userP = (User*)malloc(sizeof(User));
  
    if(NULL == userP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&userF, "users.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  printf("Please enter the ID for the user to update \n\n");

  const int userCount = displayAllUsers(&userF);

  printf("\n\n");
  char choice;
  const int catcherS1 = scanf(" %c", &choice);

  const int id = (choice - '0')-1;

  if (id > -1 && id < userCount)
  {
    GetUserAtPosition(&userF, id, userP);
  }
  else
  {
    printf("Invalid id.");
    fclose(userF);
    free(userP);
    return;
  }

    printf("What do you wish to edit? \n");
    printf("1. Name \n");
    printf("2. Username \n");
    printf("3. Password \n");
    printf("4. Role \n");
    if (strcmp(userP->department, "null") != 0)
    {
      printf("5. Department \n");
    }
    printf("\n");

    const int catcherS = scanf(" %c", &choice);

    const int aCatcher = getchar();
    if (choice == '1')
    {
      char newName[55];
      printf("\n\nNew Name: ");
      const char* intCatcher5 = fgets (newName, 55, stdin);
      strcpy(userP->name, newName);
    }
    else if (choice == '2')
    {
      char newUsername[15];
      printf("\n\nNew Username: ");
      const char* intCatcher4 = fgets (newUsername, 15, stdin);

      strcpy(userP->userName, newUsername);
    }
    else if (choice == '3')
    {
      char newPassword[15];
      printf("\n\nNew Password: ");
      const char* intCatcher3 = fgets (newPassword, 15, stdin);

      strcpy(userP->password, newPassword);
    }
    else if (choice == '4')
    {
      char newRole[8];
      printf("\n\nNew Role: ");
      const char* intCatcher2 = fgets (newRole, 8, stdin);
      strcpy(userP->role, newRole);

      if((strcmp(userP->role, "Doctor") == 0) || (strcmp(userP->role, "doctor") == 0))
      {
        printf("Please enter their department: ");
        const char* intCatcher1 = fgets(userP->department, 50, stdin);
      }
    }
    else if (choice == '5' && ((strcmp(userP->role, "Doctor") == 0) || (strcmp(userP->role, "doctor") == 0)))
    {
      char newDepartment[50];
      printf("\n\nNew Department: ");
      const char* intCatcher = fgets (newDepartment, 50, stdin);
      strcpy(userP->department, newDepartment);
    }
    else
    {
      printf("Invalid field.");
      fclose(userF);
      free(userP);
      return;
    }
    UpdateUsersFile(&userF, userP, id);
    printf("Edit saved successfully \n\n");

  fclose(userF);
  free(userP);
}

/* Menu option to remove a user account */
void removeUserAccount()
{
  FILE *userF;
  User userTable[MAX_USERS];
  User *userP = (User*)malloc(sizeof(User));
  
    if(NULL == userP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&userF, "users.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  printf("Please enter the ID for the user to remove \n\n");

  const int userCount = displayAllUsers(&userF);
  fillUserTable(&userF, userTable, userCount);

  printf("User count is %d\n", userCount);

  printf("\n\n");
  char choice;
  const int catcherS1 = scanf(" %c", &choice);

  const int id = (choice - '0')-1;

  if (id > -1 && id < userCount)
  {
    GetUserAtPosition(&userF, id, userP);
  }
  else
  {
    printf("Invalid id.\n\n");
    fclose(userF);
    free(userP);
    return;
  }

    printf("Delete %s? (y/n)", userP->name);
    const int catcherS = scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
      RewriteUsersFile(&userF, userTable, userCount, userP);
    }
    else
    {
      printf("User %s not deleted\n\n", userP->name);
      fclose(userF);
      free(userP);
      return;
    }
    printf("User %s deleted\n\n", userP->name);

  fclose(userF);
  free(userP);
}

/* Menu option to view a user account */
void viewUserAccount()
{
  FILE *userF;
  User *userP = (User*)malloc(sizeof(User));
  
    if(NULL == userP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&userF, "users.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  printf("Please enter the ID for the user to view \n\n");

  const int userCount = displayAllUsers(&userF);
  printf("\n\n");
  char choice;
  const int catcherS = scanf(" %c", &choice);

  const int id = (choice - '0')-1;

  if (id > -1 && id < userCount)
  {
    GetUserAtPosition(&userF, id, userP);
  }
  else
  {
    printf("Invalid id.\n\n");
    fclose(userF);
    free(userP);
    return;
  }
  printf("Name: %s\n", userP->name);
  printf("Username: %s\n", userP->userName);
  printf("Password: %s\n", userP->password);
  printf("Role: %s\n", userP->role);
  if (strcmp(userP->department, "null") != 0)
  {
    printf("Department: %s \n", userP->department);
  }

  printf("\n");

  fclose(userF);
  free(userP);
}

/* Look up the user and check if they exist */
/* Return 1 if they exist and 0 if they don't */
int compareAccounts(User *userToCompare)
{
  FILE *userF;
  User *userP = (User*)malloc(sizeof(User));
  
    if(NULL == userP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&userF, "users.dat") == 1)
  {
    printf("Unable to open file");
    exit(1);
  }

  int found = 1;
  while(!feof(userF))
  {
    const size_t catcher = fread(userP, sizeof(User),1, userF);
    if((strncmp(userP->userName, userToCompare->userName, 15) == 0)
    && (strncmp(userP->password, userToCompare->password, 15) == 0))
    {
      found = 0;
      break;
    }
  }
  if (found == 0)
  {
    // user is found
    strcpy(userToCompare->name, userP->name);
    strcpy(userToCompare->role, userP->role);
    strcpy(userToCompare->department, userP->department);

    fclose(userF);
    free(userP);
    return 0;
  }
  // user is not found
  fclose(userF);
  free(userP);
  return 1;
}

/* Private Functions */

void CreateUserInfo(User *newUser)
{
  char role[8];
  const int aCatcher = getchar();
  printf("Please enter the user's name: ");
  const char* intCatcher = fgets(newUser->name, 55, stdin);
  const size_t len = strlen(newUser->name);
  if (len && (newUser->name[len-1] == '\n'))
  {
    newUser->name[len-1] = '\0';
  }

  printf("Please enter their username: ");
  const char* catcher1 = fgets(newUser->userName, 15, stdin);


  printf("Please enter their password: ");
  const char* catcher2 = fgets(newUser->password, 15, stdin);


  printf("Please enter their role: ");
  const char* catcher3 = fgets(role, 8, stdin);
  strcpy(newUser->role, role);

  if((strncmp(newUser->role, "Doc", 3) == 0) || (strncmp(newUser->role, "doc", 3) == 0))
  {
    printf("Please enter their department: ");
    const char* catcher4 = fgets(newUser->department, 50, stdin);
  }
  else
  {
    strcpy(newUser->department, "null");
  }
}

int LookUpUser(FILE** file, User *userToLookUp, User *existingUser)
{
  int recPosition = 0;
  while(!feof(*file))
  {
    const size_t catcher = fread(existingUser, sizeof(User),1, *file);
    recPosition++;
    if(strcmp(existingUser->name, userToLookUp->name) == 0)
    {
      if((strcmp(existingUser->userName, userToLookUp->userName) == 0)
          && (strcmp(existingUser->password, userToLookUp->password) == 0))
      {
        return -1;
      }
      return recPosition;
    }
  }
  return 0;
}

void UpdateAccounts(int updateUser, FILE** file, User *newUser, User *existingUser)
{
  unsigned char choice = ' ';
  /* add new user? */
  if (updateUser == 0)
  {
      printf("\nConfirm addition: \n\n");

      printf("Name: %s\n", newUser->name);
      printf("Username: %s\n", newUser->userName);
      printf("Password: %s\n", newUser->password);
      printf("Role: %s \n", newUser->role);
      if (strcmp(newUser->department, "null") != 0)
      {
        printf("Department: %s \n", newUser->department);
      }
      printf("\n");

      printf("Do you wish to add this user? (y/n) ");
  }
  else if (updateUser == -1)
  {
    printf("\nDuplicate user \n");
    printf("User not added\n\n");
    return;
  }
  else /* update existing patient? */
  {
    printf("\nUser found: \n\n");

    printf("Name: %s\n", existingUser->name);
    printf("Username: %s\n", existingUser->userName);
    printf("Password: %s\n", existingUser->password);
    printf("Role: %s \n", existingUser->role);
    if (strcmp(existingUser->department, "null") != 0)
    {
      printf("Department: %s \n", existingUser->department);
    }
    printf("\n");

    printf("Do you wish to make the following changes? (y/n) ");

    if (strcmp(existingUser->userName, newUser->userName) != 0)
    {
      printf("\n\nNew Username: %s\n", newUser->userName);
    }
    if (strcmp(existingUser->password, newUser->password) != 0)
    {
      printf("New Password: %s\n", newUser->password);
    }
    if (strcmp(existingUser->role, newUser->role) != 0)
    {
      printf("New Role: %s\n", newUser->role);
    }
    if (strcmp(existingUser->department, newUser->department) != 0)
    {
      printf("New Department: %s\n", newUser->department);
    }
    printf("\n");
  }

  const int catcherS = scanf(" %c", &choice);
  if (choice == 'Y' || choice == 'y')
  {
    if (updateUser == 0)
    {
      const int catcher = AddUserToFile(file, newUser);
    }
    else
    {
      UpdateUsersFile(file, newUser, updateUser);
    }
  }
  else
  {
    printf("Changes not saved\n\n");
  }
}

int AddUserToFile(FILE** file, User *newUser)
{
  fclose(*file);
  *file = fopen("users.dat", "a+");
  if (!*file)
    return 1;
  printf("Adding user %s \n\n", newUser->name);
  const size_t catcher = fwrite(newUser, sizeof(User),1,*file);
  return 0;
}

/* Update existing patient's record with new values */
void UpdateUsersFile(FILE** file, User *newUser, int recPosition)
{
  const int catcher1 = fseek(*file, sizeof(User)*recPosition, SEEK_SET);
  printf("Updating account for %s \n\n", newUser->name);
  const size_t catcher = fwrite(newUser, sizeof(User),1,*file);
}

int displayAllUsers(FILE** file)
{
  User u;
  int id = 0;
  const int catcher1 = fseek(*file, 0, SEEK_SET);
  while(fread(&u, sizeof(User),1, *file))
  {
    id++;
    printf("%d. %s\n", id, u.name);
  }
  return id;
}

void GetUserAtPosition(FILE **file, int id, User *retrievedUser)
{
  const int catcher1 = fseek(*file, sizeof(User)*id, SEEK_SET);
  const size_t catcher = fread(retrievedUser, sizeof(User),1,*file);
    printf("User found: %s \n\n", retrievedUser->name);
}

void fillUserTable(FILE** file, User userTable[], int size)
{
  const int catcher1 = fseek(*file, 0, SEEK_SET);
  int i;
  for (i = 0; i < size; i++)
  {
    User u;
    const size_t catcher = fread(&u, sizeof(User),1, *file);
    userTable[i] = u;
  }
}

void RewriteUsersFile(FILE** file, User userTable[], int size, User *userToRemove)
{
  fclose(*file);
  *file = fopen("users.dat", "w+");
  if (!*file)
  {
    return;
  }
  int i;
  for (i = 0; i < size; i++)
  {
    User u = userTable[i];

    if ((strncmp(u.name, userToRemove->name, 4) == 0) &&
    (strncmp(u.userName, userToRemove->userName, 4) == 0))
    {
      continue;
    }
    else
    {
      const size_t catcher = fwrite(&u, sizeof(User),1, *file);
    }
  }
}
