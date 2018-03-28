/******************************************************************************

                    CEN4078 - Secure Software Development
                     Medical Records Application System

*******************************************************************************/

#include <stdio.h>
#include <string.h>

char userLoggedIn[8] = ""; //used to keep track of who is logged in
void patientRec(const char currentUser[8]);
void personalMedInfo(const char currentUser[8]);
void patientMedChart(const char currentUser[8]);
void patientMedHist(const char currentUser[8]);
void ePrescript(const char currentUser[8]);
void vital(const char currentUser[8]);
void logFunc(const char currentUser[8]);
void physicianOrder(const char currentUser[8]);
void userAcc(const char currentUser[8]);




void adminMenu (void) //First menu for Admin
{
    while(getchar() == '\n')
    {
      char choice;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Patient Records");
      printf ("\n2: User Accounts");
      printf ("\n\nOption: ");
      choice = getchar();

      switch(choice)
	    {
	        case '1':
	            patientRec("Admin");
	            break;
	        case '2':
	            userAcc("Admin");
	            break;
	        default:
	            printf ("Invalid Option!");
	    }

      if (choice == '1')
        break;
      else if(choice == '2')
        break;
    }
}

//Need to make read/write
void doctorMenu (void) //First menu for Doctor
{
    while(getchar() == '\n')
    {
      char choice;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Personal Medical Info");
      printf ("\n2: Patient Medical Chart");
      printf ("\n3: Physician Orders");
      printf ("\n4: Patient Medical History");
      printf ("\n5: E-Prescriptions");
      printf ("\n6: Vitals");
      printf ("\n7: Patient Records");
      printf ("\n\nOption: ");
      choice = getchar();

      switch(choice)
	    {
	        case '1':
	            personalMedInfo("Doctor");
	            break;
	        case '2':
	            patientMedChart("Doctor");
	            break;
	        case '3':
	            physicianOrder("Doctor");
	            break;
	        case '4':
	            patientMedHist("Doctor");
	            break;
	        case '5':
	            ePrescript("Doctor");
	            break;
	        case '6':
	            vital("Doctor");
	            break;
	        case '7':
	            patientRec("Doctor");
	            break;
	        default:
	            printf ("Invalid Option!");
	    }

      if (choice == '1')
        break;
      else if(choice == '2')
        break;
      else if(choice == '3')
        break;
      else if(choice == '4')
        break;
      else if(choice == '5')
        break;
      else if(choice == '6')
        break;
      else if(choice == '7')
        break;
    
    }
}

//Need to make read only
void patientMenu (void) //First Menu for PAtient
{
    while(getchar() == '\n')
    {
      char choice;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Personal Medical Info");
      printf ("\n2: Patient Medical History");
      printf ("\n3: E-Prescriptions");
      printf ("\n4: Vitals");
      printf ("\n5: Patient Records");
      printf ("\n\nOption: ");
      choice = getchar();

      switch(choice)
	    {
	        case '1':
	            personalMedInfo("Patient");
	            break;
	        case '2':
	            patientMedHist("Patient");
	            break;
	        case '3':
	            ePrescript("Patient");
	            break;
	        case '4':
	            vital("Patient");
	            break;
	        case '5':
	            patientRec("Patient");
	            break;
	        default:
	            printf ("Invalid Option!");
	    }

      if (choice == '1')
        break;
      else if(choice == '2')
        break;
      else if(choice == '3')
        break;
      else if(choice == '4')
        break;
      else if(choice == '5')
        break;
    
    }
}

void auditorMenu (void) //First menu for Auditor
{
    while(getchar() == '\n')
    {
      char choice;

      printf ("\n\nPlease choose from the following options: ");
      printf ("\n1: Logs");
      printf ("\n\nOption: ");
      choice = getchar();

      switch(choice)
	    {
	        case '1':
	            logFunc("Auditor");
	            break;
	        default:
	            printf ("Invalid Option!");
	    }

      if (choice == '1')
        break;
    
    }
}

void personalMedInfo(const char currentUser[8]) //This menu displays actions that can be performed for the Personal Medical Info
{
    if(currentUser == "Patient")
    {
        printf ("\n\nIt Worked Patient!!");
    }
    else if(currentUser == "Doctor")
    {
        printf ("\n\nIt Worked Doctor!!");
    }
    else
    {
        printf("\n\nError!");
    }
}

void patientMedChart(const char currentUser[8]) //This menu displays actions that can be performed for the Patient Medical Chart
{
    if(currentUser == "Doctor")
    {
        printf ("\n\nIt Worked Doctor!!"); 
    }
    else
    {
        printf("\n\nError!");
    }
}

void patientMedHist(const char currentUser[8]) //This menu displays actions that can be performed for the Patient Medical History
{
    if(currentUser == "Patient")
    {
        printf ("\n\nIt Worked Patient!!");
    }
    else if(currentUser == "Doctor")
    {
        printf ("\n\nIt Worked Doctor!!");
    }
    else
    {
        printf("\n\nError!");
    }
}

void ePrescript(const char currentUser[8]) //This menu displays actions that can be performed for the E-Prescriptions
{
    if(currentUser == "Patient")
    {
        printf ("\n\nIt Worked Patient!!");
    }
    else if(currentUser == "Doctor")
    {
        printf ("\n\nIt Worked Doctor!!");
    }
    else
    {
        printf("\n\nError!");
    }
}

void vital(const char currentUser[8]) //This menu displays actions that can be performed for the Patient's vitals
{
    if(currentUser == "Patient")
    {
        printf ("\n\nIt Worked Patient!!");
    }
    else if(currentUser == "Doctor")
    {
        printf ("\n\nIt Worked Doctor!!");
    }
    else
    {
        printf("\n\nError!");
    }
}

void logFunc(const char currentUser[8]) //This menu displays actions that can be performed for the Auditor's Logs
{
    if(currentUser == "Auditor")
    {
        printf ("\n\nIt Worked Auditor!!"); 
    }
    else
    {
        printf("\n\nError!");
    }
}

void physicianOrder(const char currentUser[8]) //This menu displays actions that can be displayed for the Personal Medical Info
{
    if(currentUser == "Doctor")
    {
        printf ("\n\nIt Worked Doctor!!"); 
    }
    else
    {
        printf("\n\nError!");
    }
}

void patientRec(const char currentUser[8]) //This menu displays actions that can be displayed for the Personal Medical Info
{
    if(currentUser == "Admin")
    {
        printf ("\n\nIt Worked Admin!!"); 
    }
    else if(currentUser == "Patient")
    {
        printf ("\n\nIt Worked Patient!!");
    }
    else if(currentUser == "Doctor")
    {
        printf ("\n\nIt Worked Doctor!!");
    }
    else
    {
        printf("\n\nError!");
    }
}

void userAcc(const char currentUser[8]) //This menu displays actions that can be displayed for the Personal Medical Info
{
    if(currentUser == "Admin")
    {
        printf ("\n\nIt Worked Admin!!"); 
    }
    else
    {
        printf("\n\nError!");
    }
}

/* int testPass(char login[8])
{
    int imp = 0;
    char adminPass[8] = "admin";
    char audPass[8] = "auditor";
    char patientPass[8] = "patient";
    char docPass[8] = "doctor";

    while(imp < 3) //covers password input and tests for authenticity
    {
        char password[16];
        
        printf("Password: ");
        scanf("%s", password);


        if (login == "Admin" && strncmp(password, adminPass, strlen(adminPass)) == 0)
	    {
	        printf("\nWelcome ");
	        printf("%s", login);
	        strncpy(userLoggedIn, login, strlen(login)); //sets global user variable
	        adminMenu();
	        break;
	    }
        else if (login == "Auditor" && strncmp(password, audPass, strlen(audPass)) == 0)
        {
            printf("\nWelcome ");
	        printf("%s", login);
	        strncpy(userLoggedIn, login, strlen(login)); //sets global user variable
	        auditorMenu();
	        break;
        }
        else if (login == "Patient" && strncmp(password, patientPass, strlen(patientPass)) == 0)
        {
            printf("\nWelcome ");
	        printf("%s", login);
	        strncpy(userLoggedIn, login, strlen(login)); //sets global user variable
	        patientMenu();
	        break;
        }
        else if (login == "Doctor" && strncmp(password, docPass, strlen(docPass)) == 0)
        {
            printf("\nWelcome ");
	        printf("%s", login);
	        strncpy(userLoggedIn, login, strlen(login)); //sets global user variable
	        doctorMenu();
	        break;
        }
        else
	    {
	        printf("\nIncorrect Login or Password!\n");
	        imp++;
	    }

        if (imp == 3)
	    {
	        printf("\n\nToo many failed login attempts. Error logged and Admin notified.");
	    }
    }
}
int main ()
{
  char choice;  
  
  printf("Welcome to the Medical Records System");
  printf("\n\nPlease choose a user: ");
  printf("\n1: Doctor");
  printf("\n2: Patient");
  printf("\n3: Admin");
  printf("\n4: Auditor");
  
  printf("\n\nOptoin: ");
  choice = getchar();
  
  switch(choice)
  {
      case '1':
        testPass("Doctor");
        break;
      case '2':
        testPass("Patient");
        break;
      case '3':
        testPass("Admin");
        break;
      case '4':
        testPass("Auditor");
        break;
      default:
        printf("Invalid Option!");
        break;
  }
  
  printf("\n\nExiting System.");

  return 0;
}*/
