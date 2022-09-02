#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutThreads.h"
#include "statStructQueue.h"

cutThreads_t cutThreads;
statStructQueue_t statQueue;

int main() {
  pthread_create(&cutThreads.readerThread, NULL, &readerFunc, NULL);
  pthread_create(&cutThreads.analyzerThread, NULL, &analyzerFunc, NULL);
  pthread_create(&cutThreads.printerThread, NULL, &printerFunc, NULL);
  pthread_create(&cutThreads.watchdogThread, NULL, &watchdogFunc, NULL);
  pthread_create(&cutThreads.loggerThread, NULL, &loggerFunc, NULL);

  pthread_join(cutThreads.readerThread, NULL);
  pthread_join(cutThreads.analyzerThread, NULL);
  pthread_join(cutThreads.printerThread, NULL);
  pthread_join(cutThreads.watchdogThread, NULL);
  pthread_join(cutThreads.loggerThread, NULL);

  printf("In main\n");
  return EXIT_SUCCESS;
}
