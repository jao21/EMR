#ifndef USERS_H
#define USERS_H

typedef struct user
{
  char name[55];
  char userName[15];
  char password[15];
  char role[8];
  char department[50];
} User;

/* Menu option to add a user account */
void addUserAccount();
/* Menu option to update an existing user account */
void updateUserAccount();
/* Menu option to remove a user account */
void removeUserAccount();
/* Menu option to view a user account */
void viewUserAccount();
/* Look up the user and check if they exist */
int compareAccounts(User *userToCompare);

#endif
