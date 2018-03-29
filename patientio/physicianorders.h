#ifndef PHYSICIANORDERS_H
#define PHYSICIANORDERS_H

/* basic data for patient */
typedef struct physOrd
{
  char sender[55];
  char staffName[55];
  char patientName[55];
  char medications[300];
  char procedures[500];
  char sequence[600];
  char feedback[300];
} PhysicianOrder;

/* Menu option to write a physician order */
void writePhysicianOrder(char *name);
/* Menu option to update an existing physician order */
void updatePhysicianOrder(char *name);
/* Menu option to view a physican order addressed to doctor logged in */
void viewPhysicianOrder(char *name);

#endif
