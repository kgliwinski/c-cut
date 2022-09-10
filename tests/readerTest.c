#include <stdlib.h>

#include "statStructQueue.h"

int main(int argc, char **argv)
{
  statStructQueue_t statQueue;
  size_t statCpuNum;

  if (!scanProcStat(&statCpuNum) || statCpuNum == 0)
  {
    return EXIT_FAILURE;
  }

  if (!initSsq(&statQueue, statCpuNum))
  {
    return EXIT_FAILURE;
  }

  statStruct_t stat = {.cpuNum = statCpuNum, .sampleTimeMS = 0, .cpu = NULL};
  stat.cpu = calloc(stat.cpuNum, sizeof(cpuStruct_t));

  return 0;
}