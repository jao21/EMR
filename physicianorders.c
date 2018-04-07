#define _CRT_SECURE_NO_DEPRECATE
#include "physicianorders.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileio.h"

int OpenFile(FILE** file, char *fileName);
void UpdateOrdersFile(FILE** file, PhysicianOrder *newOrder, int recPosition);
int displayOrders(FILE** file);
void GetOrderAtPosition(FILE **file, int id, PhysicianOrder *retrievedOrder);

void writePhysicianOrder(char *name)
{
  FILE *orderF;
  PhysicianOrder *orderP = (PhysicianOrder*)malloc(sizeof(PhysicianOrder));
  
  	if(NULL == orderP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&orderF, "orders.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  strcpy(orderP->sender, name);
  
  printf("\n\nPlease enter the staff's name: ");
  const char* Catcher1 = fgets(orderP->staffName, 55, stdin);

  const size_t len = strlen(orderP->staffName);
  if (len && (orderP->staffName[len-1] == '\n'))
  {
    orderP->staffName[len-1] = '\0';
  }

  printf("\nPlease enter the patient's name: ");
  const char* Catcher = fgets(orderP->patientName, 55, stdin);

  const size_t len2 = strlen(orderP->patientName);
  if (len2 && (orderP->patientName[len2-1] == '\n'))
  {
    orderP->patientName[len2-1] = '\0';
  }

  printf("\nPlease enter the medications needed: ");
  const char* Catcher2 = fgets(orderP->medications, 300, stdin);

  const size_t len3 = strlen(orderP->medications);
  if (len3 && (orderP->medications[len3 - 1] == '\n'))
  {
	  orderP->medications[len3 - 1] = '\0';
  }

  printf("\nPlease enter the prodedure to be performed: ");
  const char* Catcher3 = fgets(orderP->procedures, 500, stdin);
  const size_t len4 = strlen(orderP->procedures);
  if (len4 && (orderP->procedures[len4 - 1] == '\n'))
  {
	  orderP->procedures[len4 - 1] = '\0';
  }

  printf("\nPlease enter the operational sequence: ");
  const char* Catcher4 = fgets(orderP->sequence, 600, stdin);
  const size_t len5 = strlen(orderP->sequence);
  if (len5 && (orderP->sequence[len5 - 1] == '\n'))
  {
	  orderP->sequence[len5 - 1] = '\0';
  }

  printf("\nPlease enter the any kind of feedback to look out for: ");
  const char* Catcher5 = fgets(orderP->feedback, 300, stdin);
  const size_t len6 = strlen(orderP->feedback);
  if (len6 && (orderP->feedback[len6 - 1] == '\n'))
  {
	  orderP->feedback[len6 - 1] = '\0';
  }

  printf("\n\nDo you wish to make the write the order to %s for %s? (y/n)\n", orderP->staffName, orderP->patientName);

  char choice;
  char line[256];
  if (fgets(line, sizeof(line), stdin) == NULL)
  {
	  printf("Error in input");
	  return;
  }
  choice = line[0];

  
  if (choice == 'Y' || choice == 'y')
  {
    fclose(orderF);
    orderF = fopen("orders.dat", "a+");
    if (!orderF)
    {
      printf("Unable to open file");
      exit(0);
    }
    printf("Writing order to %s \n\n", orderP->staffName);
    const size_t catcherSt = fwrite(orderP, sizeof(PhysicianOrder),1,orderF);

  }
  else
  {
    printf("\nOrder not written\n\n");
  }
  fclose(orderF);
  
    if(NULL == orderP)
	{
		printf("Error");
		exit(0);
	}
	
  free(orderP);
}

void updatePhysicianOrder(const char *name)
{
  FILE *orderF;
  PhysicianOrder *orderP = (PhysicianOrder*)malloc(sizeof(PhysicianOrder));
  
    if(NULL == orderP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&orderF, "orders.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  printf("Please enter the ID of the order to update \n\n");

  const int orderCount = displayOrders(&orderF);

  printf("\n\n");
  char choice;
  char line[256];
  if (fgets(line, sizeof(line), stdin) == NULL)
  {
	  printf("Error in input");
	  return;
  }
  choice = line[0];

  const int id = (choice - '0')-1;

  if (id > -1 && id < orderCount)
  {
    GetOrderAtPosition(&orderF, id, orderP);
  }
  else
  {
    printf("Invalid id.");
    fclose(orderF);
    free(orderP);
    return;
  }
  
    printf("What do you wish to edit? \n");
    printf("1. Staff's Name \n");
    printf("2. Patient's Name \n");
    printf("3. Medications \n");
    printf("4. Procedures \n");
    printf("5. Sequence of Operations \n");
    printf("6. Feedback to note \n\n");

	char line2[256];
	if (fgets(line2, sizeof(line2), stdin) == NULL)
	{
		printf("Error in input");
		return;
	}
	choice = line2[0];
  	
    if (choice == '1')
    {
      char newName[55];
      printf("\n\nStaff's Name: ");
	  const char* Catcher = fgets(newName, 55, stdin);
	  strcpy(orderP->staffName, newName);

      const size_t len = strlen(orderP->staffName);
      if (len && (orderP->staffName[len-1] == '\n'))
      {
        orderP->staffName[len-1] = '\0';
      }
    }
    else if (choice == '2')
    {
      char newName[55];
      printf("\n\nPatient's Name: ");
	  const char* Catcher1 = fgets(newName, 55, stdin);
	  strcpy(orderP->patientName, newName);

      const size_t len2 = strlen(orderP->patientName);
      if (len2 && (orderP->patientName[len2-1] == '\n'))
      {
        orderP->patientName[len2-1] = '\0';
      }
    }
    else if (choice == '3')
    {
      char newMeds[300];
      printf("\n\nMedications: ");
      const char* Catcher2 = fgets (newMeds, 300, stdin);
      strcpy(orderP->medications, newMeds);

	  const size_t len3 = strlen(orderP->medications);
	  if (len3 && (orderP->medications[len3 - 1] == '\n'))
	  {
		  orderP->medications[len3 - 1] = '\0';
	  }
    }
    else if (choice == '4')
    {
      char newProceds[500];
      printf("\n\nProcedures: ");
      const char* Catcher3 = fgets (newProceds, 500, stdin);
      strcpy(orderP->procedures, newProceds);

	  const size_t len4 = strlen(orderP->procedures);
	  if (len4 && (orderP->procedures[len4 - 1] == '\n'))
	  {
		  orderP->procedures[len4 - 1] = '\0';
	  }
    }
    else if (choice == '5')
    {
      char newSequence[600];
      printf("\n\nSequence of Operations: ");
      const char* Catcher5 = fgets (newSequence, 600, stdin);
      strcpy(orderP->sequence, newSequence);

	  const size_t len5 = strlen(orderP->sequence);
	  if (len5 && (orderP->sequence[len5 - 1] == '\n'))
	  {
		  orderP->sequence[len5 - 1] = '\0';
	  }
    }
    else if (choice == '6')
    {
      char newFeedback[300];
      printf("\n\nFeedback to note: ");
      const char* Catcher5 = fgets (newFeedback, 300, stdin); 
      strcpy(orderP->feedback, newFeedback);

	  const size_t len6 = strlen(orderP->feedback);
	  if (len6 && (orderP->feedback[len6 - 1] == '\n'))
	  {
		  orderP->feedback[len6 - 1] = '\0';
	  }
    }
    else
    {
      printf("Invalid field.");
      fclose(orderF);
      
      if(NULL == orderP)
	  {
		printf("Error");
		exit(0);
	  }
      
      free(orderP);
      return;
    }
    UpdateOrdersFile(&orderF, orderP, id);
    printf("Edit saved successfully \n\n");

  fclose(orderF);
  free(orderP);
}

void viewPhysicianOrder(char *name)
{
  FILE *orderF;
  PhysicianOrder *orderP = (PhysicianOrder*)malloc(sizeof(PhysicianOrder));
  
    if(NULL == orderP)
	{
		printf("Error");
		exit(0);
	}

  if (OpenFile(&orderF, "orders.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }
  printf("Please select the type of orders to view \n\n");
  printf("1. Sent\n");
  printf("2. Received \n\n");
  char choice;
  
  char line[256];
  if (fgets(line, sizeof(line), stdin) == NULL)
  {
	  printf("Error in input");
	  return;
  }
  choice = line[0];

  if (choice == '1')
  {
    while(!feof(orderF))
    {
      if(fread(orderP, sizeof(PhysicianOrder),1, orderF) > 1)
  	  {
  		printf("I/O error");
    	exit(0); 	
      }
      if(strcmp(orderP->sender, name) == 0)
      {
        printf("Staff's name: %s\n", orderP->staffName);
        printf("Patient's name: %s\n", orderP->patientName);
        printf("Medications: %s\n\n", orderP->medications);
        printf("Procedures: %s\n\n", orderP->procedures);
        printf("Sequence of operations: %s\n\n", orderP->sequence);
        printf("Feedback to note: %s\n\n\n", orderP->feedback);
      }
    }
    printf("\n");
  }
  else if (choice == '2')
  {
    while(!feof(orderF))
    {
      if(fread(orderP, sizeof(PhysicianOrder),1, orderF) > 1)
  	  {
  		printf("I/O error");
    	exit(0); 	
      }
      if(strcmp(orderP->staffName, name) == 0)
      {
        printf("Sender: %s\n", orderP->sender);
        printf("Patient's name: %s\n", orderP->patientName);
        printf("Medications: %s\n\n", orderP->medications);
        printf("Procedures: %s\n\n", orderP->procedures);
        printf("Sequence of operations: %s\n\n", orderP->sequence);
        printf("Feedback to note: %s\n\n\n", orderP->feedback);
      }
    }
    printf("\n");
  }
  else
  {
    printf("Invalid field.");
  }
  fclose(orderF);
  free(orderP);
}

/* display all names and return the number of records */
int displayOrders(FILE** file)
{
  PhysicianOrder p; 
  int id = 0;
  if(fseek(*file, 0, SEEK_SET) != 0)
  {
  	
  }
  
  while(fread(&p, sizeof(PhysicianOrder),1, *file))
  {
    id++;
    printf("%d. To %s\n", id, p.staffName);
  }
  return id;
}

void GetOrderAtPosition(FILE **file, int id, PhysicianOrder *retrievedOrder)
{
  if(fseek(*file, sizeof(PhysicianOrder)*id, SEEK_SET) != 0)
  {
  	
  }
  if(fread(retrievedOrder, sizeof(PhysicianOrder),1,*file) > 1)
  {
  	printf("I/O error");
    exit(0); 	
  }
  
  printf("Order to %s for %s found \n\n", retrievedOrder->staffName, retrievedOrder->patientName);
}

void UpdateOrdersFile(FILE** file, PhysicianOrder *newOrder, int recPosition)
{
  if(fseek(*file, sizeof(PhysicianOrder)*recPosition, SEEK_SET) != 0)
  {
  	
  }
  printf("Updating order to %s for %s \n\n", newOrder->staffName, newOrder->patientName);
  const size_t catcher = fwrite(newOrder, sizeof(PhysicianOrder),1,*file);
}
