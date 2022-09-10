#include "stdlib.h"

#include "logQueue.h"
#include "logMacro.h"

/// testing mainly the initialization and freeing of queue
int main(int argc, char **argv)
{
  logQueue_t logQueue;
  if(!initLq(&logQueue))
  {
    return EXIT_FAILURE;
  }

  if (!initAq(&logQueue, 9))
  {
    printf("ERROR1\n");
    return EXIT_FAILURE;
  }

  if (!freeAq(&logQueue))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}