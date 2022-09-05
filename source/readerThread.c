#include "cutThreads.h"
#include "statStruct.h"
#include "statStructQueue.h"

#define BUFF_SIZE 20
#define TMP_SIZE 4

extern statStructQueue_t statQueue;
extern size_t statCpuNum;
extern msTimer_t cutTimer;

void *readerFunc(void *arg)
{
  (void)arg;  // to hide the unused parameter warning
  printf("Reader works!\n");
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
  statCpuNum = stat.cpuNum;
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
      printf("ERROR: wrong /proc/stat\n");
    }
    else
    {
      stat.sampleTimeMS = getTimeMst(&cutTimer);
      if (enqueueSsq(&statQueue, &stat))
      {
        printf("Enqueue works\n");
      }
    }
    usleep(READER_SLEEP_TIME);
  }

  free(buff);
  free(tmp);
  free(stat.cpu);

  return 0;
}