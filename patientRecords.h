#ifndef PATIENTRECORDS_H
#define PATIENTRECORDS_H

#include "users.h"

/* full medical chart */
typedef struct patientRecord
{
  char name[55];
  char dateOfBirth[11];
  char address[60];
  char insurance[55];
  char sex;
} Patient;

typedef struct history
{
  char name[55];
  int height;
  int weight;
  char complaint[200];
  char pastHistory[700];
  char systemsReview[400];
  char familyDiseases[300];
  char socialHistory[600];
  char regularMeds[200];
  char allergies[200];
  char sexualHistory[600];
  char conclusion[200];
} History;

typedef struct ePres
{
  char name[55];
  char prescriber[55];
  char medications[300];
  char dosage[150];
  char directions[600];
  int daw;
} EPrescription;

typedef struct vitals
{
  char name[55];
  double lastBodyTemperature;
  int lastHeartRate;
  int lastRespiratoryRate;
  int lastBloodPressure;
} Vitals;

/* Menu option to add a patient info, depending on the type */
void addPatientInfo(char *type, User *currentUser);
/* Menu option to update an existing patient info, depending on the type */
void updatePatientInfo(char *type, User *currentUser);
/* Menu option to remove an existing patient record */
void removePatientInfo();
/* Menu option to view a patient info, based on type (doctor) */
void viewPatientInfoDoc(char *type);
/* Menu option for a patient to view their own medical info */
void viewPatientInfoPat(char *type, char *name);

#endif
