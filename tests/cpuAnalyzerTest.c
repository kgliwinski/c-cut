#include <stdio.h>
#include <stdlib.h>

#include "cpuAnalyzer.h"

/// testing mainly the initialization and freeing of queue
int main(int argc, char **argv)
{
  analyzerQueue_t analyzerQueue;
  if (initAq(&analyzerQueue, 0))
  {
    return EXIT_FAILURE;
  }

  if (!initAq(&analyzerQueue, 9))
  {
    printf("ERROR1\n");
    return EXIT_FAILURE;
  }

  if (!freeAq(&analyzerQueue))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}