#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpuAnalyzer.h"
#include "cutThreads.h"
#include "logQueue.h"
#include "msTimer.h"
#include "statStructQueue.h"

cutThreads_t cutThreads;
statStructQueue_t statQueue;
logQueue_t logsQueue;
analyzerQueue_t analyzerQueue;
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
  if (!initLq(&logsQueue))
  {
    return EXIT_FAILURE;
  }
  if (!initSsq(&statQueue, statCpuNum))
  {
    // not gonna get called
    //LOG_CREATE(ERROR, "Stat queue init fail");
    printf("Stat queue init fail\n");
    return EXIT_FAILURE;
  }
  if(!initAq(&analyzerQueue, statCpuNum))
  {
    printf("Analyzer queue init fail\n");
    return EXIT_FAILURE;
  }

  pthread_create(&cutThreads.readerThread, NULL, &readerFunc, NULL);
  pthread_create(&cutThreads.analyzerThread, NULL, &analyzerFunc, NULL);
  pthread_create(&cutThreads.printerThread, NULL, &printerFunc, NULL);
  pthread_create(&cutThreads.watchdogThread, NULL, &watchdogFunc, NULL);
  pthread_create(&cutThreads.loggerThread, NULL, &loggerFunc, NULL);

  // TODO log
  LOG_CREATE(LOG, "Program starts");

  pthread_join(cutThreads.readerThread, NULL);
  pthread_join(cutThreads.analyzerThread, NULL);
  pthread_join(cutThreads.printerThread, NULL);
  pthread_join(cutThreads.watchdogThread, NULL);
  pthread_join(cutThreads.loggerThread, NULL);

  freeSsq(&statQueue);
  freeLq(&logsQueue);
  freeAq(&analyzerQueue);
  
  printf("In main\n");
  return EXIT_SUCCESS;
}
