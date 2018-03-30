#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "patientRecords.h"
#include "fileio.h"

#define MAX_PATIENTS 50

int OpenFile(FILE** file, char *fileName);

void CreatePatientInfo(Patient *newPatient);
void CreateHistory(History *history);
void CreatePres(EPrescription *pres, User *currentUser);
void CreateVitals(Vitals *vitals);

int LookUpGeneralInfo(FILE** file, Patient *patientToLookUp, Patient *existingPatient);
int LookUpHistory(FILE** file, History *historyToLookUp, History *existingHistory);
int LookUpPres(FILE** file, EPrescription *presToLookUp, EPrescription *existingPres);
int LookUpVitals(FILE** file, Vitals *vitalsToLookUp, Vitals *existingVitals);

void UpdateGeneralInfo(int updatePatient, FILE** file, Patient *newPatient, Patient *existingPatient);
void UpdateHistory(int updateHistory, FILE** file, History *newHistory, History *existingHistory);
void UpdatePres(int updatePres, FILE** file, EPrescription *newPres, EPrescription *existingPres);
void UpdateVitals(int updateVitals, FILE** file, Vitals *newVitals, Vitals *existingVitals);

void AddPatientToFile(FILE** file, Patient *newPatient);
void AddHistoryToFile(FILE** file, History *newHistory);
void AddPresToFile(FILE** file, EPrescription *newPres);
void AddVitToFile(FILE** file, Vitals *newVit);

void UpdatePatientsFile(FILE** file, Patient *newPatient, int recPosition);
void UpdateHistoryFile(FILE** file, History *newHistory, int recPosition);
void UpdatePresFile(FILE** file, EPrescription *newPres, int recPosition);
void UpdateVitFile(FILE** file, Vitals *newVit, int recPosition);

int displayAllPatients(char *type, FILE** file);

void GetGeneralAtPosition(FILE **file, int id, Patient *retrievedPatient);
void GetHistoryAtPosition(FILE **file, int id, History *retrievedHistory);
void GetPresAtPosition(FILE **file, int id, EPrescription *retrievedPres);
void GetVitalsAtPosition(FILE **file, int id, Vitals *retrievedVitals);

void UpdateName(char *oldName, char *newName, FILE **hFile, FILE **prFile, FILE **vFile,
  History *hist, EPrescription *pres, Vitals *vital);

void fillPatientTable(FILE** file, Patient *patientTable, int size);
void RewritePatientsFile(FILE** file, Patient *patientTable, int size, Patient *patientToRemove);

/* Add patient info depending on the type,
* currentUser holds any additional info that may be needed */
void addPatientInfo(char *type, User *currentUser)
{
  FILE *patientF;
  FILE *historyF;
  FILE *presF;
  FILE *vitalF;

  Patient *patientP = (Patient*)malloc(sizeof(Patient));
  
    if(NULL == patientP)
	{
		printf("Error");
		exit(0);
	}
  
  History *historyP;
  EPrescription *presP;
  Vitals *vitalP;

  const int aCatcher1 = getchar();
  printf("Please enter the patient's name: ");
  const char* intCatcher44 = fgets(patientP->name, 55, stdin);
  const size_t len = strlen(patientP->name);
  if (len && (patientP->name[len-1] == '\n'))
  {
    patientP->name[len-1] = '\0';
  }

  if (OpenFile(&patientF, "patients.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  if (strncmp(type, "General", 4) == 0)
  {
    CreatePatientInfo(patientP);
  }
  if (strncmp(type, "History", 4) == 0)
  {
    historyP = (History*)malloc(sizeof(History));
    
    if(NULL == historyP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&historyF, "history.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    strcpy(historyP->name, patientP->name);
    CreateHistory(historyP);
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0)
  {
    presP = (EPrescription*)malloc(sizeof(EPrescription));
    
    if(NULL == presP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&presF, "pres.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    strcpy(presP->name, patientP->name);
    CreatePres(presP, currentUser);
  }
  if (strncmp(type, "Vitals", 4) == 0)
  {
    vitalP = (Vitals*)malloc(sizeof(Vitals));
    
	if(NULL == vitalP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&vitalF, "vital.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    strcpy(vitalP->name, patientP->name);
    CreateVitals(vitalP);
  }

  Patient *ePatient = (Patient*)malloc(sizeof(Patient));
  
    if(NULL == ePatient)
	{
		printf("Error");
		exit(0);
	}

  const int updatePatient = LookUpGeneralInfo(&patientF, patientP, ePatient);

  if (strncmp(type, "General", 4) != 0 && updatePatient == 0)
  {
    printf("\nPatient record for %s not created yet!\n", patientP->name);
    printf("\nCreate a record for them before adding additional info\n\n");

    if (strncmp(type, "History", 4) == 0)
    {
      free(historyP);
      historyP = NULL;
      fclose(historyF);
    }
    if (strncmp(type, "E-Prescriptions", 4) == 0)
    {
      free(presP);
      presP = NULL;
      fclose(presF);
    }
    if (strncmp(type, "Vitals", 4) == 0)
    {
      free(vitalP);
      vitalP = NULL;
      fclose(vitalF);
    }
    fclose(patientF);
    free(ePatient);
    ePatient = NULL;
    free(patientP);
    return;
  }
  else
  {
    if (strncmp(type, "General", 4) == 0)
    {
      UpdateGeneralInfo(updatePatient, &patientF, patientP, ePatient);
    }
    if (strncmp(type, "History", 4) == 0)
    {
      History *eHistory = (History*)malloc(sizeof(History));
      
    if(NULL == eHistory)
	{
		printf("Error");
		exit(0);
	}
      
      const int updateHistory = LookUpHistory(&historyF, historyP, eHistory);
      UpdateHistory(updateHistory, &historyF, historyP, eHistory);
      fclose(historyF);
      free(eHistory);
      eHistory = NULL;
      free(historyP);
      historyP = NULL;
    }
    if (strncmp(type, "E-Prescriptions", 4) == 0)
    {
      EPrescription *ePres = (EPrescription*)malloc(sizeof(EPrescription));
      
      if(NULL == ePres)
	  {
		printf("Error");
		exit(0);
	  }
      
      const int updatePres = LookUpPres(&presF, presP, ePres);
      UpdatePres(updatePres, &presF, presP, ePres);
      fclose(presF);
      free(ePres);
      ePres = NULL;
      free(presP);
      presP = NULL;
    }
    if (strncmp(type, "Vitals", 4) == 0)
    {
      Vitals *eVital = (Vitals*)malloc(sizeof(Vitals));
      
    if(NULL == eVital)
	{
		printf("Error");
		exit(0);
	}
      
      const int updateVitals = LookUpVitals(&vitalF, vitalP, eVital);
      UpdateVitals(updateVitals, &vitalF, vitalP, eVital);
      fclose(vitalF);
      free(eVital);
      eVital = NULL;
      free(vitalP);
      vitalP = NULL;
    }
  }
  fclose(patientF);
  free(ePatient);
  ePatient = NULL;
  free(patientP);
}

void updatePatientInfo(char *type, User *currentUser)
{
  FILE *patientF;
  FILE *historyF;
  FILE *presF;
  FILE *vitalF;

  Patient *patientP;
  History *historyP;
  EPrescription *presP;
  Vitals *vitalP;

  printf("Please enter the ID for the patient to update \n\n");
  int patientCount = 0;
  if (strncmp(type, "General", 4) == 0)
  {
    patientP = (Patient*)malloc(sizeof(Patient));
    
    if(NULL == patientP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&patientF, "patients.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    patientCount = displayAllPatients("General", &patientF);
  }
  if (strncmp(type, "History", 4) == 0)
  {
    historyP = (History*)malloc(sizeof(History));
    
    if(NULL == historyP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&historyF, "history.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    patientCount = displayAllPatients("History", &historyF);
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0)
  {
    presP = (EPrescription*)malloc(sizeof(EPrescription));
    
    if(NULL == presP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&presF, "pres.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    patientCount = displayAllPatients("E-Prescriptions", &presF);
  }
  if (strncmp(type, "Vitals", 4) == 0)
  {
    vitalP = (Vitals*)malloc(sizeof(Vitals));
    
    if(NULL == vitalP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&vitalF, "vital.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    patientCount = displayAllPatients("Vitals", &vitalF);
  }
  printf("\n\n");

  char choice;
  const int catcherS1 = scanf(" %c", &choice);

  const int id = (choice - '0')-1;
  if (id > -1 && id < patientCount)
  {
    if (strncmp(type, "General", 4) == 0)
    {
      GetGeneralAtPosition(&patientF, id, patientP);
    }
    if (strncmp(type, "History", 4) == 0)
    {
      GetHistoryAtPosition(&historyF, id, historyP);
    }
    if (strncmp(type, "E-Prescriptions", 4) == 0)
    {
      GetPresAtPosition(&presF, id, presP);
    }
    if (strncmp(type, "Vitals", 4) == 0)
    {
      GetVitalsAtPosition(&vitalF, id, vitalP);
    }
  }
  else
  {
    printf("Invalid id.");
    if (strncmp(type, "General", 4) == 0)
    {
      fclose(patientF);
      free(patientP);
      patientP = NULL;
    }
    if (strncmp(type, "History", 4) == 0)
    {
      fclose(historyF);
      free(historyP);
      historyP = NULL;
    }
    if (strncmp(type, "E-Prescriptions", 4) == 0)
    {
      fclose(presF);
      free(presP);
      presP = NULL;
    }
    if (strncmp(type, "Vitals", 4) == 0)
    {
      fclose(vitalF);
      free(vitalP);
    }
    return;
  }
  const int aCatcher2 = getchar();
  printf("What do you wish to edit? \n");

  if (strncmp(type, "General", 4) == 0)
  {
    printf("1. Name\n");
    printf("2. Date of Birth\n");
    printf("3. Address\n");
    printf("4. Insurance Carrier\n");
    printf("5. Sex\n\n");
  }
  if (strncmp(type, "History", 4) == 0)
  {
      printf("1. Height\n");
      printf("2. Weight\n");
      printf("3. Chief complaint\n");
      printf("4. Past medical history\n");
      printf("5. Systems review\n");
      printf("6. Family diseases\n");
      printf("7. Social history\n");
      printf("8. Regular medications\n");
      printf("9. Allergies\n");
      printf("0. Sexual history\n");
      printf("A. Conclusion\n\n");
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0)
  {
      printf("1. Medications\n");
      printf("2. Dosage\n");
      printf("3. Directions\n");
      printf("4. DAW Code\n\n");
  }
  if (strncmp(type, "Vitals", 4) == 0)
  {
      printf("1. Latest body temperature\n");
      printf("2. Latest heart rate\n");
      printf("3. Latest respiratory rate\n");
      printf("4. Latest blood pressure\n\n");
  }
  const int catcherS = scanf(" %c", &choice);
  const int aCatcher1 = getchar();

  if (strncmp(type, "General", 4) == 0)
  {
    if (choice == '1')
    {
      char newName[55];
      printf("\n\nNew Name: ");
      const char* intCatcher16 = fgets (newName, 55, stdin);
      const size_t len = strlen(patientP->name);
      if (len && (patientP->name[len-1] == '\n'))
      {
        patientP->name[len-1] = '\0';
      }
      UpdateName(patientP->name, newName, &historyF, &presF, &vitalF, historyP, presP, vitalP);
      strcpy(patientP->name, newName);
    }
    else if (choice == '2')
    {
      char newDOB[11];
      printf("\n\nNew Date of Birth: ");
      const char* intCatcher15 = fgets (newDOB, 11, stdin);
      strcpy(patientP->dateOfBirth, newDOB);
    }
    else if (choice == '3')
    {
      char newAddress[60];
      printf("\n\nNew Address: ");
      const char* intCatcher14 = fgets (newAddress, 60, stdin);
      strcpy(patientP->address, newAddress);
    }
    else if (choice == '4')
    {
      char newInsurance[55];
      printf("\n\nNew Insurance Carrier: ");
      const char* intCatcher13 = fgets (newInsurance, 55, stdin);
      strcpy(patientP->insurance, newInsurance);
    }
    else if (choice == '5')
    {
      printf("\n\nChange sex: ");
      char sex;
      const int catcherS2 = scanf(" %c", &sex);

      if (sex == 'M' || sex == 'm')
      {
        patientP->sex = 'M';
      }
      else if (sex == 'F' || sex == 'f')
      {
        patientP->sex = 'F';
      }
      else
      {
        printf("Invalid field.");
        fclose(patientF);
        free(patientP);
        return;
      }
    }
    else
    {
      printf("Invalid field.");
      fclose(patientF);
      free(patientP);
      return;
    }
    UpdatePatientsFile(&patientF, patientP, id);
  }
  if (strncmp(type, "History", 4) == 0)
  {
      if (choice == '1')
      {
        int newHeight;
        printf("\n\nNew Height: ");
        const int catcherS22 = scanf(" %d", &newHeight);
        historyP->height = newHeight;
      }
      else if (choice == '2')
      {
        int newWeight;
        printf("\n\nNew Weight: ");
        const int catcherS17 = scanf(" %d", &newWeight);
        historyP->weight = newWeight;
      }
      else if (choice == '3')
      {
        char newComplaint[200];
        printf("\n\nNew Complaint: ");
        const char* intCatcher11 = fgets (newComplaint, 200, stdin);
        strcpy(historyP->complaint, newComplaint);
      }
      else if (choice == '4')
      {
        char newPast[700];
        printf("\n\nNewest Past History: ");
        const char* intCatcher10 = fgets (newPast, 700, stdin);
        strcpy(historyP->pastHistory, newPast);
      }
      else if (choice == '5')
      {
        char newReview[400];
        printf("\n\nNewest Systems Review: ");
        const char* intCatcher9 = fgets (newReview, 400, stdin);
        strcpy(historyP->systemsReview, newReview);
      }
      else if (choice == '6')
      {
        char newDis[300];
        printf("\n\nNewest Family Diseases: ");
        const char* intCatcher8 = fgets (newDis, 300, stdin);
        strcpy(historyP->familyDiseases, newDis);
      }
      else if (choice == '7')
      {
        char newSoc[600];
        printf("\n\nNewest Social History: ");
        const char* intCatcher7 = fgets (newSoc, 600, stdin);
        strcpy(historyP->socialHistory, newSoc);
      }
      else if (choice == '8')
      {
        char newMeds[200];
        printf("\n\nNewest Regular Medications: ");
        const char* intCatcher6 = fgets (newMeds, 200, stdin);
        strcpy(historyP->regularMeds, newMeds);
      }
      else if (choice == '9')
      {
        char newAll[200];
        printf("\n\nNewest Allergies: ");
        const char* intCatcher5 = fgets (newAll, 200, stdin);
        strcpy(historyP->allergies, newAll);
      }
      else if (choice == '0')
      {
        char newSex[600];
        printf("\n\nNewest Sexual History: ");
        const char* intCatcher4 = fgets (newSex, 600, stdin);
        strcpy(historyP->sexualHistory, newSex);
      }
      else if (choice == 'A')
      {
        char newCon[200];
        printf("\n\nNewest Conclusion: ");
        const char* intCatcher3 = fgets (newCon, 200, stdin);
        strcpy(historyP->conclusion, newCon);
      }
      else
      {
        printf("Invalid field.");
        fclose(historyF);
        free(historyP);
        return;
      }
      UpdateHistoryFile(&historyF, historyP, id);
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0)
  {
      if (choice == '1')
      {
        char newMeds[300];
        printf("\n\nNew Medications: ");
        const char* intCatcher2 = fgets (newMeds, 300, stdin);
        strcpy(presP->medications, newMeds);
        strcpy(presP->prescriber, currentUser->name);
      }
      else if (choice == '2')
      {
        char newDos[150];
        printf("\n\nNew Dosage: ");
        const char* intCatcher1 = fgets (newDos, 150, stdin);
        strcpy(presP->dosage, newDos);
        strcpy(presP->prescriber, currentUser->name);
      }
      else if (choice == '3')
      {
        char newDir[600];
        printf("\n\nNew Directions: ");
        const char* intCatcher = fgets (newDir, 150, stdin);
        strcpy(presP->directions, newDir);
        strcpy(presP->prescriber, currentUser->name);
      }
      else if (choice == '4')
      {
        int newDAW;
        printf("\n\nNew DAW Code: ");
        const int catcherS4 = scanf(" %d", &newDAW);
        presP->daw = newDAW;
        strcpy(presP->prescriber, currentUser->name);
      }
      else
      {
        printf("Invalid field.");
        fclose(presF);
        free(presP);
        return;
      }
      UpdatePresFile(&presF, presP, id);
  }
  if (strncmp(type, "Vitals", 4) == 0)
  {
      printf("1. Latest body temperature\n");
      printf("2. Latest heart rate\n");
      printf("3. Latest respiratory rate\n");
      printf("4. Latest blood pressure\n\n");

      if (choice == '1')
      {
        double newTemp;
        printf("\n\nNewest body temperature: ");
        const int catcherS3 = scanf(" %lf", &newTemp);
        vitalP->lastBodyTemperature = newTemp;
      }
      else if (choice == '2')
      {
        int newHeart;
        printf("\n\nNewest Heart Rate: ");
        const int catcherS2 = scanf(" %d", &newHeart);
        vitalP->lastHeartRate = newHeart;
      }
      else if (choice == '3')
      {
        int newResp;
        printf("\n\nNewest Respiratory Rate: ");
        const int catcherS14 = scanf(" %d", &newResp);
        vitalP->lastRespiratoryRate = newResp;
      }
      else if (choice == '4')
      {
        int newBlood;
        printf("\n\nNewest Blood Pressure: ");
        const int catcherS31 = scanf(" %d", &newBlood);
        vitalP->lastBloodPressure = newBlood;
      }
      else
      {
        printf("Invalid field.");
        fclose(vitalF);
        free(vitalP);
        return;
      }
      UpdateVitFile(&vitalF, vitalP, id);
  }
  printf("Edit saved successfully \n\n");

  if (strncmp(type, "General", 4) == 0)
  {
    fclose(patientF);
    free(patientP);
    patientP = NULL;
  }
  if (strncmp(type, "History", 4) == 0)
  {
    fclose(historyF);
    free(historyP);
    historyP = NULL;
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0)
  {
    fclose(presF);
    free(presP);
    presP = NULL;
  }
  if (strncmp(type, "Vitals", 4) == 0)
  {
    fclose(vitalF);
    free(vitalP);
    vitalP = NULL;
  }
}

void removePatientInfo()
{
  FILE *patientF;
  Patient patientTable[MAX_PATIENTS];
  Patient *patientP = (Patient*)malloc(sizeof(Patient));
  
    if(NULL == patientP)
	{
		printf("Error");
		exit(0);
	}
  

  if (OpenFile(&patientF, "patients.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  printf("Please enter the ID for the patient to remove \n\n");

  const int patientCount = displayAllPatients("General", &patientF);
  fillPatientTable(&patientF, patientTable, patientCount);

  printf("\n\n");
  char choice;
  const int catcherS = scanf(" %c", &choice);

  const int id = (choice - '0')-1;

  if (id > -1 && id < patientCount)
  {
    GetGeneralAtPosition(&patientF, id, patientP);
  }
  else
  {
    printf("Invalid id.\n\n");
    fclose(patientF);
    free(patientP);
    return;
  }
    printf("Delete %s? (y/n)", patientP->name);

    const int catcherS21 = scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
      RewritePatientsFile(&patientF, patientTable, patientCount, patientP);
    }
    else
    {
      printf("Patient %s not deleted\n\n", patientP->name);
      fclose(patientF);
      free(patientP);
      return;
    }
    printf("Patient %s deleted\n\n", patientP->name);

  fclose(patientF);
  free(patientP);
}

void viewPatientInfoDoc(char *type)
{
  FILE *patientF;

  Patient *patientP;

  printf("Please enter the name of the patient to view \n\n");

  patientP = (Patient*)malloc(sizeof(Patient));
  
    if(NULL == patientP)
	{
		printf("Error");
		exit(0);
	}
  
  if (OpenFile(&patientF, "patients.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }
  if(displayAllPatients("General", &patientF) != 0)
  {
    const int aCatcher01 = getchar();
    char name[55];
    const char* intCatcher99 = fgets(name,55,stdin);
    const size_t len = strlen(name);
    if (len && (name[len-1] == '\n'))
    {
      name[len-1] = '\0';
    }

    fclose(patientF);
    free(patientP);
    patientP = NULL;
    viewPatientInfoPat(type, name);
  }
  printf("\n\n");

}

void viewPatientInfoPat(char *type, char *name)
{
  FILE *patientF;
  FILE *historyF;
  FILE *presF;
  FILE *vitalF;

  Patient *patientP;
  History *historyP;
  EPrescription *presP;
  Vitals *vitalP;

  if (strncmp(type, "General", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    patientP = (Patient*)malloc(sizeof(Patient));
    
    if(NULL == patientP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&patientF, "patients.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    while(!feof(patientF))
    {
      const size_t catcher3 = fread(patientP, sizeof(Patient),1, patientF);
      if(strcmp(patientP->name, name) == 0)
      {
        const int aCatcher4 = getchar();
        printf("Name: %s\n", patientP->name);
        printf("Date of Birth: %s\n", patientP->dateOfBirth);
        printf("Address: %s\n", patientP->address);
        printf("Insurance Carrier: %s\n", patientP->insurance);
        printf("Sex: %c \n\n", patientP->sex);
        break;
      }
    }
  }
  if (strncmp(type, "History", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    historyP = (History*)malloc(sizeof(History));
    
    if(NULL == historyP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&historyF, "history.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    while(!feof(historyF))
    {
      const size_t catcher2 = fread(historyP, sizeof(History),1, historyF);
      if(strcmp(historyP->name, name) == 0)
      {
        const int aCatcher3 = getchar();
        printf("Name: %s\n", historyP->name);
        printf("Height: %d\n", historyP->height);
        printf("Weight: %d\n", historyP->weight);
        printf("Chief complaint: %s\n", historyP->complaint);
        printf("Past medical history: %s\n", historyP->pastHistory);
        printf("Systems review: %s\n", historyP->systemsReview);
        printf("Family diseases: %s\n", historyP->familyDiseases);
        printf("Social history: %s\n", historyP->socialHistory);
        printf("Regular medications: %s\n", historyP->regularMeds);
        printf("Allergies: %s\n", historyP->allergies);
        printf("Sexual history: %s\n", historyP->sexualHistory);
        printf("Conclusion: %s\n\n", historyP->conclusion);
        break;
      }
    }
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    presP = (EPrescription*)malloc(sizeof(EPrescription));
    
    if(NULL == presP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&presF, "pres.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    while(!feof(presF))
    {
      const size_t catcher1 = fread(presP, sizeof(EPrescription),1, presF);
      if(strcmp(presP->name, name) == 0)
      {
        const int aCatcher2 = getchar();
        printf("Name: %s\n", presP->name);
        printf("Medications: %s\n", presP->medications);
        printf("Dosage: %s\n", presP->dosage);
        printf("Directions: %s\n", presP->directions);
        printf("DAW Code: %d\n\n", presP->daw);
        break;
      }
    }
  }
  if (strncmp(type, "Vitals", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    vitalP = (Vitals*)malloc(sizeof(Vitals));
    
    if(NULL == vitalP)
	{
		printf("Error");
		exit(0);
	}
    
    if (OpenFile(&vitalF, "vital.dat") == 1)
    {
      printf("Unable to open file");
      exit(0);
    }
    while(!feof(vitalF))
    {
      const size_t catcher77 = fread(vitalP, sizeof(Vitals),1, vitalF);
      if(strcmp(vitalP->name, name) == 0)
      {
        const int aCatcher1 = getchar();
        printf("Name: %s\n", vitalP->name);
        printf("Latest body temperature: %f", vitalP->lastBodyTemperature);
        printf("\nLatest heart rate: %d", vitalP->lastHeartRate);
        printf("\nLatest respiratory rate: %d", vitalP->lastRespiratoryRate);
        printf("\nLatest blood pressure: %d\n\n", vitalP->lastBloodPressure);
        break;
      }
    }
  }
  printf("\n");
  if (strncmp(type, "General", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    fclose(patientF);
    free(patientP);
    patientP = NULL;
  }
  if (strncmp(type, "History", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    fclose(historyF);
    free(historyP);
    historyP = NULL;
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    fclose(presF);
    free(presP);
    presP = NULL;
  }
  if (strncmp(type, "Vitals", 4) == 0 || strncmp(type, "All", 3) == 0)
  {
    fclose(vitalF);
    free(vitalP);
    vitalP = NULL;
  }
}

/* Create new patient's info */
void CreatePatientInfo(Patient *newPatient)
{
  printf("Please enter their date of birth: ");
  const char* intCatcher2 = fgets(newPatient->dateOfBirth, 11, stdin);

  printf("Please enter their address: ");
  const char* intCatcher1 = fgets(newPatient->address, 60, stdin);

  printf("Please enter their insurance carrier: ");
  const char* intCatcher = fgets(newPatient->insurance, 55, stdin);

  printf("Please enter their sex: ");
  const int catcherS = scanf(" %c", &newPatient->sex);
}

void CreateHistory(History *history)
{
  printf("Please enter the patient's height: ");
  const int catcherS2 = scanf(" %d", &history->height);

  printf("Please enter their weight: ");
  const int catcherS1 = scanf(" %d", &history->weight);

  const int aCatcher = getchar();
  printf("Please enter their chief complaint: ");
  const char* intCatcher8 = fgets(history->complaint, 200, stdin);

  printf("Please enter any past medical history: ");
  const char* intCatcher7 = fgets(history->pastHistory, 700, stdin);

  printf("Please enter their systems review, if applicable: ");
  const char* intCatcher6 = fgets(history->systemsReview, 400, stdin);

  printf("Please enter any family diseases: ");
  const char* intCatcher5 = fgets(history->familyDiseases, 300, stdin);

  printf("Please enter their social history: ");
  const char* intCatcher4 = fgets(history->socialHistory, 600, stdin);

  printf("Please enter any regular medications: ");
  const char* intCatcher3 = fgets(history->regularMeds, 200, stdin);

  printf("Please enter any allergies: ");
  const char* intCatcher2 = fgets(history->allergies, 200, stdin);

  printf("Please enter their sexual history, if applicable: ");
  const char* intCatcher1 = fgets(history->sexualHistory, 600, stdin);

  printf("Conclusion: ");
  const char* intCatcher = fgets(history->conclusion, 200, stdin);

  printf("\n");
}

void CreatePres(EPrescription *pres, User *currentUser)
{
  strcpy(pres->prescriber, currentUser->name);
  printf("Please enter the patient's medications: ");
  const char* intCatcher2 = fgets(pres->medications, 300, stdin);

  printf("Please enter the dosage information: ");
  const char* intCatcher1 = fgets(pres->dosage, 150, stdin);

  printf("Please enter directions: ");
  const char* intCatcher = fgets(pres->directions, 600, stdin);

  printf("Please enter the DAW Code: ");
  const int catcherS = scanf(" %d", &pres->daw);

  printf("\n");
}

void CreateVitals(Vitals *vitals)
{
  printf("\nPlease enter their latest body temperature: ");
  double newTemp;
  const int catcherS3 = scanf(" %lf", &newTemp);
  vitals->lastBodyTemperature = newTemp;

  printf("\nPlease enter their latest heart rate: ");
  int newHeart;
  const int catcherS2 = scanf(" %d", &newHeart);
  vitals->lastHeartRate = newHeart;

  printf("\nPlease enter their latest respiratory rate: ");
  int newResp;
  const int catcherS11 = scanf(" %d", &newResp);
  vitals->lastRespiratoryRate = newResp;

  printf("\nPlease enter their latest blood pressure: ");
  int newBlood;
  const int catcherS = scanf(" %d", &newBlood);
  vitals->lastBloodPressure = newBlood;

  printf("\n");
}

/* Search for existing patient
* and return whether to update;
* the record's position in the file is returned if can update
* else, 0 is returned */
int LookUpGeneralInfo(FILE** file, Patient *patientToLookUp, Patient *existingPatient)
{
  int recPosition = 0;
  while(!feof(*file))
  {
    const size_t catcher4 = fread(existingPatient, sizeof(Patient),1, *file);
    recPosition++;
    if(strcmp(existingPatient->name, patientToLookUp->name) == 0)
    {
      return recPosition;
    }
  }
  return 0;
}

int LookUpHistory(FILE** file, History *historyToLookUp, History *existingHistory)
{
  int recPosition = 0;
  while(!feof(*file))
  {
    const size_t catcher3 = fread(existingHistory, sizeof(History),1, *file);
    recPosition++;
    if(strcmp(existingHistory->name, historyToLookUp->name) == 0)
    {
      return recPosition;
    }
  }
  return 0;
}
int LookUpPres(FILE** file, EPrescription *presToLookUp, EPrescription *existingPres)
{
  int recPosition = 0;
  while(!feof(*file))
  {
    const size_t catcher2 = fread(existingPres, sizeof(EPrescription),1, *file);
    recPosition++;
    if(strcmp(existingPres->name, presToLookUp->name) == 0)
    {
      return recPosition;
    }
  }
  return 0;
}
int LookUpVitals(FILE** file, Vitals *vitalsToLookUp, Vitals *existingVitals)
{
  int recPosition = 0;
  while(!feof(*file))
  {
    const size_t catcher1 = fread(existingVitals, sizeof(Vitals),1, *file);
    recPosition++;
    if(strcmp(existingVitals->name, vitalsToLookUp->name) == 0)
    {
      return recPosition;
    }
  }
  return 0;
}

/* Determines whether to update existing info or add new patient */
void UpdateGeneralInfo(int updatePatient, FILE** file, Patient *newPatient, Patient *existingPatient)
{
  unsigned char choice = ' ';
  /* add new patient? */
  if (updatePatient == 0)
  {
      printf("\nConfirm addition for %s: \n\n", newPatient->name);

      printf("Date of Birth: %s\n", newPatient->dateOfBirth);
      printf("Address: %s\n", newPatient->address);
      printf("Insurance Carrier: %s\n", newPatient->insurance);
      printf("Sex: %c \n\n", newPatient->sex);

      printf("Do you wish to add this info? (y/n) ");
  }
  else /* update existing patient? */
  {
    printf("\nPatient %s found \n\n", existingPatient->name);

    printf("Date of Birth: %s\n", existingPatient->dateOfBirth);
    printf("Address: %s\n", existingPatient->address);
    printf("Insurance Carrier: %s\n", existingPatient->insurance);
    printf("Sex: %c \n\n", existingPatient->sex);

    printf("Do you wish to make changes? (y/n) \n");

    printf("\n");
  }

  const int catcherS = scanf(" %c", &choice);
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

void UpdateHistory(int updateHistory, FILE** file, History *newHistory, History *existingHistory)
{
  unsigned char choice = ' ';
  /* add new patient? */
  if (updateHistory == 0)
  {
    printf("\nConfirm addition for %s: \n\n", newHistory->name);

    printf("Height: %d\n", newHistory->height);
    printf("Weight: %d\n", newHistory->weight);
    printf("Chief complaint: %s\n", newHistory->complaint);
    printf("Past medical history: %s\n", newHistory->pastHistory);
    printf("Systems review: %s\n", newHistory->systemsReview);
    printf("Family diseases: %s\n", newHistory->familyDiseases);
    printf("Social history: %s\n", newHistory->socialHistory);
    printf("Regular medications: %s\n", newHistory->regularMeds);
    printf("Allergies: %s\n", newHistory->allergies);
    printf("Sexual history: %s\n", newHistory->sexualHistory);
    printf("Conclusion: %s\n\n", newHistory->conclusion);

    printf("Do you wish to add this info? (y/n) ");
  }
  else /* update existing patient? */
  {
    printf("\nPatient %s found \n\n", existingHistory->name);

    printf("Height: %d\n", existingHistory->height);
    printf("Weight: %d\n", existingHistory->weight);
    printf("Chief complaint: %s\n", existingHistory->complaint);
    printf("Past medical history: %s\n", existingHistory->pastHistory);
    printf("Systems review: %s\n", existingHistory->systemsReview);
    printf("Family diseases: %s\n", existingHistory->familyDiseases);
    printf("Social history: %s\n", existingHistory->socialHistory);
    printf("Regular medications: %s\n", existingHistory->regularMeds);
    printf("Allergies: %s\n", existingHistory->allergies);
    printf("Sexual history: %s\n", existingHistory->sexualHistory);
    printf("Conclusion: %s\n\n", existingHistory->conclusion);

    printf("Do you wish to make changes? (y/n) \n");
  }
  printf("\n");

  const int catcherS = scanf(" %c", &choice);
  if (choice == 'Y' || choice == 'y')
  {
    if (updateHistory == 0)
    {
      AddHistoryToFile(file, newHistory);
    }
    else
    {
      UpdateHistoryFile(file, newHistory, updateHistory);
    }
  }
  else
  {
    printf("Changes not saved\n\n");
  }
}

void UpdatePres(int updatePres, FILE** file, EPrescription *newPres, EPrescription *existingPres)
{
  unsigned char choice = ' ';
  /* add new patient? */
  if (updatePres == 0)
  {
      printf("\nConfirm addition for %s: \n\n", newPres->name);

      printf("Medications: %s\n", newPres->medications);
      printf("Dosage: %s\n", newPres->dosage);
      printf("Directions: %s\n", newPres->directions);
      printf("DAW Code: %d\n\n", newPres->daw);

      printf("Do you wish to add this info? (y/n) ");
  }
  else /* update existing patient? */
  {
    printf("\nPatient %s found \n\n", existingPres->name);

    printf("Medications: %s\n", existingPres->medications);
    printf("Dosage: %s\n", existingPres->dosage);
    printf("Directions: %s\n", existingPres->directions);
    printf("DAW Code: %d\n\n", existingPres->daw);

    printf("Do you wish to make changes? (y/n) \n");

    printf("\n");
  }

  const int catcherS = scanf(" %c", &choice);
  if (choice == 'Y' || choice == 'y')
  {
    if (updatePres == 0)
    {
      AddPresToFile(file, newPres);
    }
    else
    {
      UpdatePresFile(file, newPres, updatePres);
    }
  }
  else
  {
    printf("Changes not saved\n\n");
  }
}

void UpdateVitals(int updateVitals, FILE** file, Vitals *newVitals, Vitals *existingVitals)
{
  char choice = ' ';
  /* add new patient? */
  if (updateVitals == 0)
  {
      printf("\nConfirm addition for %s: \n\n", newVitals->name);

      printf("Latest body temperature: %f", newVitals->lastBodyTemperature);
      printf("\nLatest heart rate: %d", newVitals->lastHeartRate);
      printf("\nLatest respiratory rate: %d", newVitals->lastRespiratoryRate);
      printf("\nLatest blood pressure: %d\n\n", newVitals->lastBloodPressure);

      printf("Do you wish to add this info? (y/n) ");
  }
  else /* update existing patient? */
  {
    printf("\nPatient %s found \n\n", existingVitals->name);

    printf("Latest body temperature: %f", existingVitals->lastBodyTemperature);
    printf("\nLatest heart rate: %d", existingVitals->lastHeartRate);
    printf("\nLatest respiratory rate: %d", existingVitals->lastRespiratoryRate);
    printf("\nLatest blood pressure: %d\n\n", existingVitals->lastBloodPressure);

    printf("Do you wish to make changes? (y/n) \n");

    printf("\n");
  }

  const int catcherS = scanf(" %c", &choice);
  if (choice == 'Y' || choice == 'y')
  {
    if (updateVitals == 0)
    {
      AddVitToFile(file, newVitals);
    }
    else
    {
      UpdateVitFile(file, newVitals, updateVitals);
    }
  }
  else
  {
    printf("Changes not saved\n\n");
  }
}

/* Append to file if no patient found */
void AddPatientToFile(FILE** file, Patient *newPatient)
{
  fclose(*file);
  *file = fopen("patients.dat", "a+");
  if (!*file)
    exit(1);
  printf("Adding record for %s \n\n", newPatient->name);

  const size_t catcher = fwrite(newPatient, sizeof(Patient),1,*file);
}

void AddHistoryToFile(FILE** file, History *newHistory)
{
  fclose(*file);
  *file = fopen("history.dat", "a+");
  if (!*file)
    exit(1);
  printf("Adding record for %s \n\n", newHistory->name);

  const size_t catcher = fwrite(newHistory, sizeof(History),1,*file);
}

void AddPresToFile(FILE** file, EPrescription *newPres)
{
  fclose(*file);
  *file = fopen("pres.dat", "a+");
  if (!*file)
    exit(1);
  printf("Adding record for %s \n\n", newPres->name);

  const size_t catcher = fwrite(newPres, sizeof(EPrescription),1,*file);
}

void AddVitToFile(FILE** file, Vitals *newVit)
{
  fclose(*file);
  *file = fopen("vital.dat", "a+");
  if (!*file)
    exit(1);
  printf("Adding record for %s \n\n", newVit->name);

  const size_t catcher = fwrite(newVit, sizeof(Vitals),1,*file);
}

/* Update existing patient's record with new values */
void UpdatePatientsFile(FILE** file, Patient *newPatient, int recPosition)
{
  const int catcher1 = fseek(*file, sizeof(Patient)*recPosition, SEEK_SET);
  printf("Updating record for %s \n\n", newPatient->name);
  const size_t catcher = fwrite(newPatient, sizeof(Patient),1,*file);
}

void UpdateHistoryFile(FILE** file, History *newHistory, int recPosition)
{
  const int catcher1 = fseek(*file, sizeof(History)*recPosition, SEEK_SET);
  printf("Updating record for %s \n\n", newHistory->name);
  const size_t catcher = fwrite(newHistory, sizeof(History),1,*file);
}

void UpdatePresFile(FILE** file, EPrescription *newPres, int recPosition)
{
  const int catcher1 = fseek(*file, sizeof(EPrescription)*recPosition, SEEK_SET);
  printf("Updating record for %s \n\n", newPres->name);
  const size_t catcher = fwrite(newPres, sizeof(EPrescription),1,*file);
}

void UpdateVitFile(FILE** file, Vitals *newVit, int recPosition)
{
  const int catcher1 = fseek(*file, sizeof(Vitals)*recPosition, SEEK_SET);
  printf("Updating record for %s \n\n", newVit->name);
  const size_t catcher = fwrite(newVit, sizeof(Vitals),1,*file);
}

/* display all names and return the number of records */
int displayAllPatients(char *type, FILE** file)
{
  int id = 0;
  if (strncmp(type, "General", 4) == 0)
  {
    Patient p;
    const int catcher3 = fseek(*file, 0, SEEK_SET);
    while(fread(&p, sizeof(Patient),1, *file))
    {
      id++;
      printf("%d. %s\n", id, p.name);
    }
  }
  if (strncmp(type, "History", 4) == 0)
  {
    History h;
    const int catcher2 = fseek(*file, 0, SEEK_SET);
    while(fread(&h, sizeof(History),1, *file))
    {
      id++;
      printf("%d. %s\n", id, h.name);
    }
  }
  if (strncmp(type, "E-Prescriptions", 4) == 0)
  {
    EPrescription e;
    const int catcher1 = fseek(*file, 0, SEEK_SET);
    while(fread(&e, sizeof(EPrescription),1, *file))
    {
      id++;
      printf("%d. %s\n", id, e.name);
    }
  }
  if (strncmp(type, "Vitals", 4) == 0)
  {
    Vitals v;
    const int catcher = fseek(*file, 0, SEEK_SET);
    while(fread(&v, sizeof(Vitals),1, *file))
    {
      id++;
      printf("%d. %s\n", id, v.name);
    }
  }
  return id;
}

void fillPatientTable(FILE** file, Patient patientTable[], int size)
{
  const int catcher1 = fseek(*file, 0, SEEK_SET);
  int i;
  for (i = 0; i < size; i++)
  {
    Patient p;
    const size_t catcher = fread(&p, sizeof(Patient),1, *file);
    patientTable[i] = p;
  }
}

void GetGeneralAtPosition(FILE **file, int id, Patient *retrievedPatient)
{
  const int catcher1 = fseek(*file, sizeof(Patient)*id, SEEK_SET);
  const size_t catcher = fread(retrievedPatient, sizeof(Patient),1,*file);
  printf("Patient found: %s \n\n", retrievedPatient->name);
}

void GetHistoryAtPosition(FILE **file, int id, History *retrievedHistory)
{
  const int catcher1 = fseek(*file, sizeof(History)*id, SEEK_SET);
  const size_t catcher = fread(retrievedHistory, sizeof(History),1,*file);
  printf("Patient found: %s \n\n", retrievedHistory->name);
}

void GetPresAtPosition(FILE **file, int id, EPrescription *retrievedPres)
{
  const int catcher1 = fseek(*file, sizeof(EPrescription)*id, SEEK_SET);
  const size_t catcher = fread(retrievedPres, sizeof(EPrescription),1,*file);
  printf("Patient found: %s \n\n", retrievedPres->name);
}

void GetVitalsAtPosition(FILE **file, int id, Vitals *retrievedVitals)
{
  const int catcher1 = fseek(*file, sizeof(Vitals)*id, SEEK_SET);
  const size_t catcher = fread(retrievedVitals, sizeof(Vitals),1,*file);
  printf("Patient found: %s \n\n", retrievedVitals->name);
}

void UpdateName(char *oldName, char *newName, FILE **hFile, FILE **prFile, FILE **vFile,
  History *hist, EPrescription *pres, Vitals *vital)
{
  hist = (History*)malloc(sizeof(History));
  
    if(NULL == hist)
	{
		printf("Error");
		exit(0);
	}
  
  if (OpenFile(hFile, "history.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  pres = (EPrescription*)malloc(sizeof(EPrescription));
  
    if(NULL == pres)
	{
		printf("Error");
		exit(0);
	}
  
  if (OpenFile(prFile, "pres.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  vital = (Vitals*)malloc(sizeof(Vitals));
  
    if(NULL == vital)
	{
		printf("Error");
		exit(0);
	}
  
  if (OpenFile(vFile, "vital.dat") == 1)
  {
    printf("Unable to open file");
    exit(0);
  }

  int position = -1;
  while(!feof(*hFile))
  {
    position++;
    const size_t catcher51 = fread(hist, sizeof(History),1, *hFile);
    if(strcmp(hist->name, oldName) == 0)
    {
      strcpy(hist->name, newName);
       const int catcher3 = fseek(*hFile, sizeof(History)*position, SEEK_SET);
      const size_t catcher4 = fwrite(hist, sizeof(History),1,*hFile);
      break;
    }
  }
  position = -1;
  while(!feof(*prFile))
  {
    const size_t catcher3 = fread(pres, sizeof(EPrescription),1, *prFile);
    position++;
    if(strcmp(pres->name, oldName) == 0)
    {
      strcpy(pres->name, newName);
      const int catcher2 = fseek(*prFile, sizeof(EPrescription)*position, SEEK_SET);
      const size_t catcher1 = fwrite(pres, sizeof(EPrescription),1,*prFile);
      break;
    }
  }
  position = -1;
  while(!feof(*vFile))
  {
    const size_t catcher2 = fread(vital, sizeof(Vitals),1, *vFile);
    position++;
    if(strcmp(vital->name, oldName) == 0)
    {
      strcpy(vital->name, newName);
      const int catcher1 = fseek(*vFile, sizeof(Vitals)*position, SEEK_SET);
      const size_t catcher = fwrite(vital, sizeof(Vitals),1,*vFile);
      break;
    }
  }
  fclose(*hFile);
  free(hist);
  hist = NULL;

  fclose(*prFile);
  free(pres);
  pres = NULL;

  fclose(*vFile);
  free(vital);
  vital = NULL;
}

void RewritePatientsFile(FILE** file, Patient patientTable[], int size, Patient *patientToRemove)
{
  fclose(*file);
  *file = fopen("patients.dat", "w+");
  if (!*file)
  {
    return;
  }
  //fseek(*file, 0, SEEK_SET);
  int i;
  for (i = 0; i < size; i++)
  {
    Patient p = patientTable[i];
    //printf("patienttable %d name %s", i, patientTable[i].name);
    //printf("p %d name %s", i, p.name);
    if ((strncmp(p.name, patientToRemove->name, 4) == 0) &&
    (strncmp(p.dateOfBirth, patientToRemove->dateOfBirth, 4) == 0))
    {
      continue;
    }
    else
    {
      const size_t catcher = fwrite(&p, sizeof(Patient),1, *file);
    }
  }
}
