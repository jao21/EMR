#include "fileio.h"

int OpenFile(FILE** file, char *fileName)
{
  *file = fopen(fileName, "r+");
  if (!*file)
  {
        *file = fopen(fileName, "w+");
        if (!*file)
        {
          return 1;
        }
  }
  return 0;
}
