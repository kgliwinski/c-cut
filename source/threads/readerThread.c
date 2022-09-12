#include "cutThreads.h"
#include "logQueue.h"
#include "statStruct.h"
#include "statStructQueue.h"


#define BUFF_SIZE 20
#define TMP_SIZE 4

extern cutThreads_t cutThreads;
extern statStructQueue_t statQueue;
extern logQueue_t logsQueue;
extern size_t statCpuNum;
extern msTimer_t cutTimer;

extern watchdogStruct_t wd;

void *readerFunc(void *arg)
{
  (void)arg;  // to hide the unused parameter warning
  cutThreads.reader.pid = getpid();
  pthread_mutex_lock(&cutThreads.reader.mutex);
  char *buff = calloc(BUFF_SIZE, sizeof(char));
  wd.readerPtr.buff = buff;
  char *tmp = calloc(TMP_SIZE, sizeof(char));
  wd.readerPtr.tmp = tmp;
  FILE *procStat = NULL;
  wd.readerPtr.procStat = procStat;

  statStruct_t stat = {.cpuNum = statCpuNum, .sampleTimeMS = 0, .cpu = NULL};
  stat.cpu = calloc(stat.cpuNum, sizeof(cpuStruct_t));
  wd.readerPtr.stat = &stat;

  tmp[TMP_SIZE - 1] = '\0';
  // str = readProcStat();
  wd.freeReader = 0;
  while (cutThreads.reader.run)
  {
    // measure sample time
    if (!readProcStat(buff, tmp, procStat, &stat))
    {
      LOG_CREATE(ERROR, "/proc/stat not read");
    }
    else
    {
      stat.sampleTimeMS = getTimeMst(&cutTimer);
      if (enqueueSsq(&statQueue, &stat))
      {
        // printf("Enqueue works\n");
        // createLogLq(0, "Enqueue works!", &logsQueue, __FILE__, __LINE__);
      }
      else
      {
        LOG_CREATE(LOG, "Stat not enqueued");
      }
    }
    usleep(READER_SLEEP_TIME);
  }

  free(buff);
  free(tmp);
  free(stat.cpu);
  wd.freeReader = 1;
  pthread_mutex_unlock(&cutThreads.reader.mutex);
  return 0;
}