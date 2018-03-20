#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <time.h>

/* basic patient data for now */
struct rec
{
  char name[55];
  char address[60];
  char insurance[55];
  char sex;
};

typedef struct rec PatientRec;

int OpenFile(FILE** file);
void CreatePatientInfo(PatientRec *newPatient);
int LookUpPatient(FILE** file, PatientRec *patientToLookUp, PatientRec *existingPatient);
void UpdateRecords(int updatePatient, FILE** file, PatientRec *newPatient, PatientRec *existingPatient);
int AddPatientToFile(FILE** file, PatientRec *newPatient);
void UpdatePatientsFile(FILE** file, PatientRec *newPatient, int recPosition);

int main ()
{
  FILE *patientF;
  PatientRec patientToAdd;
  PatientRec *p2APtr = (PatientRec*)malloc(sizeof(PatientRec));

  if (OpenFile(&patientF) == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  CreatePatientInfo(p2APtr);

  PatientRec existingPatient;
  PatientRec *ePPtr = (PatientRec*)malloc(sizeof(PatientRec));
  int updatePatient = LookUpPatient(&patientF, p2APtr, ePPtr);

  UpdateRecords(updatePatient, &patientF, p2APtr, ePPtr);
  free(p2APtr);
  free(ePPtr);
}

/* Open the file, create one if it doesn't exist */
int OpenFile(FILE** file)
{
  *file = fopen("p_recs.dat", "r+");
  if (!*file)
  {
        *file = fopen("p_recs.dat", "w+");
        if (!*file)
        {
          return 1;
        }
  }
  return 0;
}

/* Create new patient's info */
void CreatePatientInfo(PatientRec *newPatient)
{
  printf("Please enter the patient's name: ");
  fgets(newPatient->name, 55, stdin);

  printf("Please enter their address: ");
  fgets(newPatient->address, 60, stdin);

  printf("Please enter their insurance carrier: ");
  fgets(newPatient->insurance, 55, stdin);

  printf("Please enter their sex: ");
  scanf(" %c", &newPatient->sex);
}

/* Search for existing patient
* and return whether to update;
* the record's position in the file is returned if can update
* else, 0 is returned */
int LookUpPatient(FILE** file, PatientRec *patientToLookUp, PatientRec *existingPatient)
{
  int recPosition = 0;
  while(!feof(*file))
  {
    fread(existingPatient, sizeof(PatientRec),1, *file);
    recPosition++;
    if(strcmp(existingPatient->name, patientToLookUp->name) == 0)
    {
      if((strcmp(existingPatient->address, patientToLookUp->address) == 0)
          && (strcmp(existingPatient->insurance, patientToLookUp->insurance) == 0)
          && existingPatient->sex == patientToLookUp->sex)
      {
        return -1;
      }
      return recPosition;
    }
  }
  return 0;
}

/* Determines whether to update existing info or add new patient */
void UpdateRecords(int updatePatient, FILE** file, PatientRec *newPatient, PatientRec *existingPatient)
{
  char choice = ' ';
  /* add new patient? */
  if (updatePatient == 0)
  {
      printf("\nConfirm addition: \n\n");

      printf("Name: %s\n", newPatient->name);
      printf("Address: %s\n", newPatient->address);
      printf("Insurance Carrier: %s\n", newPatient->insurance);
      printf("Sex: %c \n\n", newPatient->sex);

      printf("Do you wish to add this patient? (y/n) ");
  }
  else if (updatePatient == -1)
  {
    printf("\nDuplicate record \n");
    printf("Record not added\n\n");
    return;
  }
  else /* update existing patient? */
  {
    printf("\nPatient found: \n\n");

    printf("Name: %s\n", existingPatient->name);
    printf("Address: %s\n", existingPatient->address);
    printf("Insurance Carrier: %s\n", existingPatient->insurance);
    printf("Sex: %c \n\n", existingPatient->sex);

    printf("Do you wish to make the following changes? (y/n) ");

    if (strcmp(existingPatient->address, newPatient->address) != 0)
    {
      printf("\n\nNew Address: %s\n", newPatient->address);
    }
    if (strcmp(existingPatient->insurance, newPatient->insurance) != 0)
    {
      printf("New Insurance Carrier: %s\n", newPatient->insurance);
    }
    if (existingPatient->sex != newPatient->sex)
    {
      printf("Changed sex: %c\n", newPatient->sex);
    }
    printf("\n");
  }

  scanf(" %c", &choice);
  if (choice == 'Y' || choice == 'y')
  {
    if (updatePatient == 0)
    {
      AddPatientToFile(file, newPatient);
    }
    else
    {
      UpdatePatientsFile(file, newPatient, updatePatient);
    }
  }
  else
  {
    printf("Changes not saved\n\n");
  }
}

/* Append to file if no patient founf */
int AddPatientToFile(FILE** file, PatientRec *newPatient)
{
  fclose(*file);
  *file = fopen("p_recs.dat", "a+");
  if (!*file)
    return 1;
  printf("Adding record for %s \n\n", newPatient->name);
  fwrite(&newPatient, sizeof(PatientRec),1,*file);
  return 0;
}

/* Update existing patient's record with new values */
void UpdatePatientsFile(FILE** file, PatientRec *newPatient, int recPosition)
{
  fseek(*file, sizeof(PatientRec)*recPosition, SEEK_SET);
  printf("Updating record for %s \n\n", newPatient->name);
  fwrite(&newPatient, sizeof(PatientRec),1,*file);
}
