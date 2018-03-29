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

  if (OpenFile(&orderF, "orders.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  strcpy(orderP->sender, name);

  getchar();
  printf("\n\nPlease enter the staff's name: ");
  fgets(orderP->staffName, 55, stdin);
  size_t len = strlen(orderP->staffName);
  if (len && (orderP->staffName[len-1] == '\n'))
  {
    orderP->staffName[len-1] = '\0';
  }

  printf("\nPlease enter the patient's name: ");
  fgets(orderP->patientName, 55, stdin);
  len = strlen(orderP->patientName);
  if (len && (orderP->patientName[len-1] == '\n'))
  {
    orderP->patientName[len-1] = '\0';
  }

  printf("\nPlease enter the medications needed: ");
  fgets(orderP->medications, 300, stdin);

  printf("\nPlease enter the prodedure to be performed: ");
  fgets(orderP->procedures, 500, stdin);

  printf("\nPlease enter the operational sequence: ");
  fgets(orderP->sequence, 600, stdin);

  printf("\nPlease enter the any kind of feedback to look out for: ");
  fgets(orderP->feedback, 300, stdin);

  printf("\n\nDo you wish to make the write the order to %s for %s? (y/n)\n", orderP->staffName, orderP->patientName);

  char choice;
  scanf(" %c", &choice);
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
    fwrite(orderP, sizeof(PhysicianOrder),1,orderF);
  }
  else
  {
    printf("\nOrder not written\n\n");
  }
  fclose(orderF);
  free(orderP);
}

void updatePhysicianOrder(char *name)
{
  FILE *orderF;
  PhysicianOrder *orderP = (PhysicianOrder*)malloc(sizeof(PhysicianOrder));

  if (OpenFile(&orderF, "orders.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  printf("Please enter the ID of the order to update \n\n");

  int orderCount = displayOrders(&orderF);

  printf("\n\n");
  char choice;
  scanf(" %c", &choice);

  int id = (choice - '0')-1;

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
    getchar();
    printf("What do you wish to edit? \n");
    printf("1. Staff's Name \n");
    printf("2. Patient's Name \n");
    printf("3. Medications \n");
    printf("4. Procedures \n");
    printf("5. Sequence of Operations \n");
    printf("6. Feedback to note \n\n");

    scanf(" %c", &choice);

    getchar();
    if (choice == '1')
    {
      char newName[55];
      printf("\n\nStaff's Name: ");
      size_t len = strlen(orderP->staffName);
      if (len && (orderP->staffName[len-1] == '\n'))
      {
        orderP->staffName[len-1] = '\0';
      }
      fgets (newName, 55, stdin);
      strcpy(orderP->staffName, newName);
    }
    else if (choice == '2')
    {
      char newName[55];
      printf("\n\nPatient's Name: ");
      size_t len = strlen(orderP->patientName);
      if (len && (orderP->patientName[len-1] == '\n'))
      {
        orderP->patientName[len-1] = '\0';
      }
      fgets (newName, 55, stdin);
      strcpy(orderP->patientName, newName);
    }
    else if (choice == '3')
    {
      char newMeds[300];
      printf("\n\nMedications: ");
      fgets (newMeds, 300, stdin);
      strcpy(orderP->medications, newMeds);
    }
    else if (choice == '4')
    {
      char newProceds[500];
      printf("\n\nProcedures: ");
      fgets (newProceds, 500, stdin);
      strcpy(orderP->procedures, newProceds);
    }
    else if (choice == '5')
    {
      char newSequence[600];
      printf("\n\nSequence of Operations: ");
      fgets (newSequence, 600, stdin);
      strcpy(orderP->sequence, newSequence);
    }
    else if (choice == '6')
    {
      char newFeedback[300];
      printf("\n\nFeedback to note: ");
      fgets (newFeedback, 300, stdin);
      strcpy(orderP->feedback, newFeedback);
    }
    else
    {
      printf("Invalid field.");
      fclose(orderF);
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

  if (OpenFile(&orderF, "orders.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }
  printf("Please select the type of orders to view \n\n");
  printf("1. Sent\n");
  printf("2. Received \n\n");
  char choice;
  scanf(" %c", &choice);

  if (choice == '1')
  {
    while(!feof(orderF))
    {
      fread(orderP, sizeof(PhysicianOrder),1, orderF);
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
      fread(orderP, sizeof(PhysicianOrder),1, orderF);
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
  fseek(*file, 0, SEEK_SET);
  while(fread(&p, sizeof(PhysicianOrder),1, *file))
  {
    id++;
    printf("%d. To %s\n", id, p.staffName);
  }
  return id;
}

void GetOrderAtPosition(FILE **file, int id, PhysicianOrder *retrievedOrder)
{
  fseek(*file, sizeof(PhysicianOrder)*id, SEEK_SET);
  fread(retrievedOrder, sizeof(PhysicianOrder),1,*file);
  printf("Order to %s for %s found \n\n", retrievedOrder->staffName, retrievedOrder->patientName);
}

void UpdateOrdersFile(FILE** file, PhysicianOrder *newOrder, int recPosition)
{
  fseek(*file, sizeof(PhysicianOrder)*recPosition, SEEK_SET);
  printf("Updating order to %s for %s \n\n", newOrder->staffName, newOrder->patientName);
  fwrite(newOrder, sizeof(PhysicianOrder),1,*file);
}
