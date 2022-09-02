#include "cutThreads.h"
#include "statStruct.h"
#include "statStructQueue.h"

#define BUFF_SIZE 20
#define TMP_SIZE 4
#define SLEEP_TIME 1.0f
#define MAX_QUEUE_SIZE 25

extern statStructQueue_t statQueue;

void *readerFunc(void *arg)
{
  (void)arg;  // to hide the unused parameter warning
  printf("Reader works!\n");
  struct timespec time;
  int i = 0;
  char *buff = calloc(BUFF_SIZE, sizeof(char));
  char *tmp = calloc(TMP_SIZE, sizeof(char));
  FILE *procStat = fopen("/proc/stat", "r");
  rewind(procStat);

  statStruct_t stat;

  if (!scanProcStat(buff, tmp, procStat, &stat))
  {
    // TODO log
    printf("ERROR: Cannot scan /proc/stat\n");
  }
  fclose(procStat);
  stat.cpu = calloc(stat.cpuNum, sizeof(cpuStruct_t));

  statQueue = (statStructQueue_t){
      0, 0, MAX_QUEUE_SIZE, malloc(MAX_QUEUE_SIZE * sizeof(statStruct_t))};
  for (i = 0; i < MAX_QUEUE_SIZE; ++i)
  {
    statQueue.stats[i].cpu = calloc(stat.cpuNum, sizeof(cpuStruct_t));
  }
  tmp[TMP_SIZE - 1] = '\0';
  // str = readProcStat();
  i = 0;
  while (i++ < 3)
  {
    if ((procStat = fopen("/proc/stat", "r")) != NULL)
    {
      // measure sample time
      clock_gettime(CLOCK_MONOTONIC_RAW, &time);
      stat.sampleTimeMS = time.tv_sec * 1000000 + time.tv_sec / 1000;
      rewind(procStat);
      if (!readProcStat(buff, tmp, procStat, &stat))
      {
        // TODO log
        printf("ERROR: cannot open /proc/stat\n");
      }
      fclose(procStat);
      if (enqueue(&statQueue, &stat))
      {
        printf("Enqueue works\n");
      }
      printf("%i\n", isEmpty(&statQueue));
      sleep(SLEEP_TIME);
    }
    else
    {
      sleep(SLEEP_TIME);
    }
  }
  i = 0;
  while (i < 3)
  {
    if (dequeue(&statQueue, &stat))
    {
      printf("Dequeue works\n");
    }
    printProcStat(&stat);
    i++;
  }
  free(buff);
  free(tmp);
  free(stat.cpu);
  free(statQueue.stats);
  // TODO free statQueue.stats.cpu
  return 0;
}