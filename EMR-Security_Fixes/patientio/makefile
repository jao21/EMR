app : client.o menus.o physicianorders.o patientRecords.o users.o fileio.o
	cc -o app client.o menus.o physicianorders.o patientRecords.o users.o fileio.o

client.o : client.c users.h menus.h
	cc -c client.c
menus.o : menus.c menus.h users.h patientRecords.h physicianorders.h
	cc -c menus.c
physicianorders.o : physicianorders.c physicianorders.h fileio.h
	cc -c physicianorders.c
patientRecords.o : patientRecords.c patientRecords.h fileio.h users.h
	cc -c patientRecords.c
users.o : users.c users.h fileio.h
	cc -c users.c
fileio.o : fileio.c fileio.h
	cc -c fileio.c


clean :
	rm app client.o menus.o physicianorders.o patientRecords.o users.o fileio.o