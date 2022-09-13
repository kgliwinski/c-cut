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
  
  // values taken from manual proc/stat analyzing
  cpuStruct_t prev = { 649328, 119, 101725, 5908274, 6106, 0, 37192, 0, 0, 0};
  cpuStruct_t cur = {650408, 119, 101742, 5908274, 6106, 0, 37192, 0, 0, 0};

  if(calculateCpuUsePerc(prev, cur) != 100.0f)
  {
    printf("%f\n",calculateCpuUsePerc(prev, cur));
    return EXIT_FAILURE;
  }

  if (!freeAq(&analyzerQueue))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}