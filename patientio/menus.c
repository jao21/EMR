/******************************************************************************

                    CEN4078 - Secure Software Development
                     Medical Records Application System

*******************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "menus.h"
#include <stdio.h>
#include <string.h>
#include "patientRecords.h"
#include "physicianorders.h"

#define BUFFERSIZE 10

void patientRec(User *userLoggedIn);
void patientMedChart(User *userLoggedIn);
void patientMedHist(User *userLoggedIn);
void ePrescript(User *userLoggedIn);
void vital(User *userLoggedIn);
void logFunc(User *userLoggedIn);
void physicianOrder(User *userLoggedIn);
void userAcc(User *userLoggedIn);

void addPatientInfo(char *type, User *currentUser);
void updatePatientInfo(char *type, User *currentUser);
void removePatientInfo();
void viewPatientInfoDoc(char *type);
void viewPatientInfoPat(char *type, char *name);

void writePhysicianOrder(char *name);
void updatePhysicianOrder(const char *name);
void viewPhysicianOrder(char *name);

void addUserAccount();
void updateUserAccount();
void removeUserAccount();
void viewUserAccount();
int compareAccounts(User *userToCompare);

void adminMenu (User *userLoggedIn) //First menu for Admin
{
    char choice;
    do
    {
    //  int inc = 0;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Patient Records");
      printf ("\n2: User Accounts");
      printf ("\nPress q to logout");
      printf ("\n\nOption: ");
      if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      {
    	choice = choice;
	  }

      switch(choice)
	    {
	        case '1':
	            patientRec(userLoggedIn);
	            break;
	        case '2':
	            userAcc(userLoggedIn);
	            break;
          case 'q':
          case 'Q':
              return;
	        default:
	            printf ("Invalid Option!");
	    }
    } while (choice != 'q' || choice != 'Q');
}

void doctorMenu (User *userLoggedIn) //First menu for Doctor
{
    char choice;
    do
    {
    //  int inc = 0;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Patient Medical Chart");
      printf ("\n2: Physician Orders");
      printf ("\n3: Patient Medical History");
      printf ("\n4: E-Prescriptions");
      printf ("\n5: Vitals");
      printf ("\n6: Patient Records");
      printf ("\nPress q to logout");
      printf ("\n\nOption: ");
      if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      {
    	choice = choice;
	  }


      switch(choice)
	    {
	        case '1':
	            patientMedChart(userLoggedIn);
	            break;
	        case '2':
	            physicianOrder(userLoggedIn);
	            break;
	        case '3':
	            patientMedHist(userLoggedIn);
	            break;
	        case '4':
	            ePrescript(userLoggedIn);
	            break;
	        case '5':
	            vital(userLoggedIn);
	            break;
	        case '6':
	            patientRec(userLoggedIn);
	            break;
          case 'q':
          case 'Q':
              return;
	        default:
	            printf ("Invalid Option!");
	    }
    } while (choice != 'q' || choice != 'Q');
}

void patientMenu (User *userLoggedIn) //First Menu for Nurse
{
    char choice;
    do
    {
    //  int inc = 0;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Patient Medical History");
      printf ("\n2: E-Prescriptions");
      printf ("\n3: Vitals");
      printf ("\n4: General Info");
      printf ("\nPress q to logout");
      printf ("\n\nOption: ");
      if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      {
    	choice = choice;
	  }


      switch(choice)
	    {
	        case '1':
	            patientMedHist(userLoggedIn);
	            break;
	        case '2':
	            ePrescript(userLoggedIn);
	            break;
	        case '3':
	            vital(userLoggedIn);
	            break;
	        case '4':
	            patientRec(userLoggedIn);
	            break;
          case 'q':
          case 'Q':
              return;
	        default:
	            printf ("Invalid Option!");
	    }

    } while (choice != 'q' || choice != 'Q');
}

void auditorMenu (User *userLoggedIn) //First menu for Auditor
{
    char choice;
    do
    {
   //   int inc = 0;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Logs");
      printf ("\nPress q to logout");
      printf ("\n\nOption: ");
      if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      {
    	choice = choice;
	  }


      switch(choice)
	    {
	        case '1':
	            logFunc(userLoggedIn);
	            break;
          case 'q':
          case 'Q':
              return;
	        default:
	            printf ("Invalid Option!");
	    }

    } while (choice != 'q' || choice != 'Q');
}

void patientMedChart(User *userLoggedIn) //This menu displays actions that can be performed for the Patient Medical Chart
{
    char choice;
    if(strncmp(userLoggedIn->role,"Doctor", 4) == 0)
    {
      do
      {
        printf("Selected -> Medical Charts \n");
        printf("1. View \n");
        printf("Press q or Q to exit \n\n");
      if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      {
    	choice = choice;
	  }


        if (choice == '1')
        {
          viewPatientInfoDoc("All");
        }
        else
        {
          printf("Exiting Medical Charts");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');
    }
    else
    {
        printf("\n\nError!");
    }
}

void patientMedHist(User *userLoggedIn) //This menu displays actions that can be performed for the Patient Medical History
{
    char choice;
    if(strncmp(userLoggedIn->role,"Patient", 4) == 0)
    {
        viewPatientInfoPat("History", userLoggedIn->name);
    }
    else if(strncmp(userLoggedIn->role,"Doctor", 4) == 0)
    {
      do
      {
        printf("Selected -> Medical History \n");
        printf("1. View \n");
        printf("2. Add \n");
        printf("3. Update \n");
        printf("Press q or Q to exit \n\n");
      	if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      	{
    		choice = choice;
	  	}


        if (choice == '1')
        {
          viewPatientInfoDoc("History");
        }
        else if (choice == '2')
        {
          addPatientInfo("History", userLoggedIn);
        }
        else if (choice == '3')
        {
          updatePatientInfo("History", userLoggedIn);
        }
        else
        {
          printf("Exiting Medical History");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');

    }
    else
    {
        printf("\n\nError!");
    }
}

void ePrescript(User *userLoggedIn) //This menu displays actions that can be performed for the E-Prescriptions
{
    char choice;
    if(strncmp(userLoggedIn->role,"Patient", 4) == 0)
    {
      viewPatientInfoPat("E-Prescriptions", userLoggedIn->name);
    }
    else if(strncmp(userLoggedIn->role,"Doctor", 4) == 0)
    {
      do
      {
        printf("Selected -> E-Prescriptions \n");
        printf("1. View \n");
        printf("2. Add \n");
        printf("3. Update \n");
        printf("Press q or Q to exit \n\n");
      	if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      	{
    		choice = choice;
	  	}


        if (choice == '1')
        {
          viewPatientInfoDoc("E-Prescriptions");
        }
        else if (choice == '2')
        {
          addPatientInfo("E-Prescriptions", userLoggedIn);
        }
        else if (choice == '3')
        {
          updatePatientInfo("E-Prescriptions", userLoggedIn);
        }
        else
        {
          printf("Exiting E-Prescriptions");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');
    }
    else
    {
        printf("\n\nError!");
    }
}

void vital(User *userLoggedIn) //This menu displays actions that can be performed for the Patient's vitals
{
    char choice;
    if(strncmp(userLoggedIn->role,"Patient", 4) == 0)
    {
      viewPatientInfoPat("Vitals", userLoggedIn->name);
    }
    else if(strncmp(userLoggedIn->role,"Doctor", 4) == 0)
    {
      do
      {
        printf("Selected -> Vitals \n");
        printf("1. View \n");
        printf("2. Add \n");
        printf("3. Update \n");
        printf("Press q or Q to exit \n\n");
      	if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      	{
    		choice = choice;
	  	}


        if (choice == '1')
        {
          viewPatientInfoDoc("Vitals");
        }
        else if (choice == '2')
        {
          addPatientInfo("Vitals", userLoggedIn);
        }
        else if (choice == '3')
        {
          updatePatientInfo("Vitals", userLoggedIn);
        }
        else
        {
          printf("Exiting Vitals");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');
    }
    else
    {
        printf("\n\nError!");
    }
}

void logFunc(User *userLoggedIn) //This menu displays actions that can be performed for the Auditor's Logs
{
    if(strncmp(userLoggedIn->role,"Auditor", 4) == 0)
    {
        printf ("\n\nIt Worked Auditor!!");
    }
    else
    {
        printf("\n\nError!");
    }
}

void physicianOrder(User *userLoggedIn) //This menu displays actions that can be displayed for the Personal Medical Info
{
    char choice;
    if(strncmp(userLoggedIn->role,"Doctor", 4) == 0)
    {
      do
      {
        printf("Selected -> Physician Orders \n");
        printf("1. View \n");
        printf("2. Write \n");
        printf("3. Update \n");
        printf("Press q or Q to exit \n\n");
      	if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      	{
    		choice = choice;
	  	}


        if (choice == '1')
        {
          viewPhysicianOrder(userLoggedIn->name);
        }
        else if (choice == '2')
        {
          writePhysicianOrder(userLoggedIn->name);
        }
        else if (choice == '3')
        {
          updatePhysicianOrder(userLoggedIn->name);
        }
        else
        {
          printf("Exiting Physician Orders");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');
    }
    else
    {
        printf("\n\nError!");
    }
}

void patientRec(User *userLoggedIn) //This menu displays actions that can be displayed for the Personal Medical Info
{
    char choice;
    if(strncmp(userLoggedIn->role,"Admin", 4) == 0)
    {
      do
      {
        printf("Selected -> Patient Records \n");
        printf("1. Add \n");
        printf("2. Update \n");
        printf("3. Remove \n");
        printf("Press q or Q to exit \n\n");
     	if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      	{
    		choice = choice;
	 	}


        if (choice == '1')
        {
          addPatientInfo("General", userLoggedIn);
        }
        else if (choice == '2')
        {
          updatePatientInfo("General", userLoggedIn);
        }
        else if (choice == '3')
        {
          removePatientInfo();
        }
        else
        {
          printf("Exiting Patient Records");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');
    }
    else if(strncmp(userLoggedIn->role,"Patient", 4) == 0)
    {
        viewPatientInfoPat("General", userLoggedIn->name);
    }
    else if(strncmp(userLoggedIn->role,"Doctor", 4) == 0)
    {
      do
      {
        printf("Selected -> Patient Records \n");
        printf("1. View \n");
        printf("2. Add \n");
        printf("3. Update \n");
        printf("Press q or Q to exit \n\n");
      	if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      	{
    		choice = choice;
	  	}


        if (choice == '1')
        {
          viewPatientInfoDoc("General");
        }
        else if (choice == '2')
        {
          addPatientInfo("General", userLoggedIn);
        }
        else if (choice == '3')
        {
          updatePatientInfo("General", userLoggedIn);
        }
        else
        {
          printf("Exiting Patient Records");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');
    }
    else
    {
        printf("\n\nError!");
    }
}

void userAcc(User *userLoggedIn) //This menu displays actions that can be displayed for the Personal Medical Info
{
    char choice;
    if(strncmp(userLoggedIn->role,"Admin", 4) == 0)
    {
      do
      {
        printf("Selected -> User Accounts \n");
        printf("1. View \n");
        printf("2. Add \n");
        printf("3. Update \n");
        printf("4. Remove \n");
        printf("Press q or Q to exit \n\n");
      	if (fgets(&choice, BUFFERSIZE, stdin) != NULL)
      	{
    		choice = choice;
	  	}


        if (choice == '1')
        {
          viewUserAccount();
        }
        else if (choice == '2')
        {
          addUserAccount();
        }
        else if (choice == '3')
        {
          updateUserAccount();
        }
        else if (choice == '4')
        {
          removeUserAccount();
        }
        else
        {
          printf("Exiting User Accounts");
          return;
        }
        printf("\n");
      } while (choice != 'q' || choice != 'Q');
    }
    else
    {
        printf("\n\nError!");
    }
}
