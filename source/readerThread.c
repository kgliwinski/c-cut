#include "cutThreads.h"
#include "statStruct.h"
#include "statStructQueue.h"

#define BUFF_SIZE 20
#define TMP_SIZE 4
#define SLEEP_TIME 1.0f

extern statStructQueue_t statQueue;

void *readerFunc(void *arg)
{
  (void)arg;  // to hide the unused parameter warning
  printf("Reader works!\n");
  struct timespec time;
  int i = 0;
  char *buff = calloc(BUFF_SIZE, sizeof(char));
  char *tmp = calloc(TMP_SIZE, sizeof(char));
  FILE *procStat = NULL;

  statStruct_t stat = {.cpuNum = 0, .sampleTimeMS = 0, .cpu = NULL};

  if (!scanProcStat(buff, tmp, procStat, &stat))
  {
    // TODO log
    printf("ERROR: Cannot scan /proc/stat\n");
  }

  stat.cpu = calloc(stat.cpuNum, sizeof(cpuStruct_t));

  if (!initSsq(&statQueue, &stat))
  {
    // TODO log
    printf("Error init\n");
  }

  tmp[TMP_SIZE - 1] = '\0';
  // str = readProcStat();
  i = 0;
  while (i++ < 3)
  {
    // measure sample time
    if (!readProcStat(buff, tmp, procStat, &stat))
    {
      // TODO log
      printf("ERROR: cannot open /proc/stat\n");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
    stat.sampleTimeMS = time.tv_sec * 1000000 + time.tv_sec / 1000;
    if (enqueueSsq(&statQueue, &stat))
    {
      printf("Enqueue works\n");
    }
    sleep(SLEEP_TIME);
  }

  i = 0;
  while (i < 3)
  {
    if (dequeueSsq(&statQueue, &stat))
    {
      printf("Dequeue works\n");
    }
    printProcStat(&stat);
    i++;
  }
  free(buff);
  free(tmp);
  freeSsq(&statQueue);
  free(stat.cpu);
  // TODO free statQueue.stats.cpu
  return 0;
}