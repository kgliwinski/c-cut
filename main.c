#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutThreads.h"
#include "statStructQueue.h"
#include "msTimer.h"

cutThreads_t cutThreads;
statStructQueue_t statQueue;
size_t statCpuNum;
msTimer_t cutTimer;

int main()
{
  initMst(&cutTimer);
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
  printf("In main\n");
  return EXIT_SUCCESS;
}
