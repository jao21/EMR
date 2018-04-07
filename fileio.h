#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

/* Open the file, create one if it doesn't exist */
int OpenFile(FILE** file, char *fileName);

#endif
