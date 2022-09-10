#include "cutThreads.h"
#include "statStruct.h"
#include "statStructQueue.h"
#include "logQueue.h"

#define BUFF_SIZE 20
#define TMP_SIZE 4

extern statStructQueue_t statQueue;
extern logQueue_t logsQueue;
extern size_t statCpuNum;
extern msTimer_t cutTimer;

void *readerFunc(void *arg)
{
  (void)arg;  // to hide the unused parameter warning
  int i = 0;
  char *buff = calloc(BUFF_SIZE, sizeof(char));
  char *tmp = calloc(TMP_SIZE, sizeof(char));
  FILE *procStat = NULL;

  statStruct_t stat = {.cpuNum = statCpuNum, .sampleTimeMS = 0, .cpu = NULL};

  stat.cpu = calloc(stat.cpuNum, sizeof(cpuStruct_t));

  tmp[TMP_SIZE - 1] = '\0';
  // str = readProcStat();
  i = 0;
  while (1)
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
        // printf("Enqueue works\n");
        //createLogLq(0, "Enqueue works!", &logsQueue, __FILE__, __LINE__);
        LOG_CREATE(0, "Enqueue works!");
      }
    }
    usleep(READER_SLEEP_TIME);
  }

  free(buff);
  free(tmp);
  free(stat.cpu);

  return 0;
}