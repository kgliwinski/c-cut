#include "cutThreads.h"
#include "statStructQueue.h"

extern statStructQueue_t statQueue;
extern size_t statCpuNum;
void *analyzerFunc(void *arg)
{
  (void)arg;
  printf("Analyzer works!\n");
  size_t i = 0;
  while (isEmptySsq(&statQueue))
  {
    sleep(1);
  }
  statStruct_t stat = {.cpuNum = statCpuNum, .sampleTimeMS = 0, .cpu = NULL};

  stat.cpu = calloc(stat.cpuNum, sizeof(cpuStruct_t));
  while (i < 3)
  {
    if (dequeueSsq(&statQueue, &stat))
    {
      printf("Dequeue works\n");
      printProcStat(&stat);
      i++;
    }
    usleep(ANALYZER_SLEEP_TIME);
  }
  free(stat.cpu);

  return 0;
}