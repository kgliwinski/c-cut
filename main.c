#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutThreads.h"
#include "logQueue.h"
#include "msTimer.h"
#include "statStructQueue.h"

cutThreads_t cutThreads;
statStructQueue_t statQueue;
logQueue_t logsQueue;
size_t statCpuNum;
msTimer_t cutTimer;

int main()
{
  if (!scanProcStat(&statCpuNum))
  {
    printf("ERROR: Cannot scan /proc/stat\n");
    return EXIT_FAILURE;
  }
  initMst(&cutTimer);
  initLq(&logsQueue);
  if (!initSsq(&statQueue, statCpuNum))
  {
    LOG_CREATE(ERROR, "Stat queue init fail");
  }
  
  pthread_create(&cutThreads.readerThread, NULL, &readerFunc, NULL);
  pthread_create(&cutThreads.analyzerThread, NULL, &analyzerFunc, NULL);
  pthread_create(&cutThreads.printerThread, NULL, &printerFunc, NULL);
  pthread_create(&cutThreads.watchdogThread, NULL, &watchdogFunc, NULL);
  pthread_create(&cutThreads.loggerThread, NULL, &loggerFunc, NULL);

  // TODO log
  printf("START TIME: %lu\n", getTimeMst(&cutTimer));

  pthread_join(cutThreads.readerThread, NULL);
  pthread_join(cutThreads.analyzerThread, NULL);
  pthread_join(cutThreads.printerThread, NULL);
  pthread_join(cutThreads.watchdogThread, NULL);
  pthread_join(cutThreads.loggerThread, NULL);

  freeSsq(&statQueue);
  freeLq(&logsQueue);
  printf("In main\n");
  return EXIT_SUCCESS;
}
