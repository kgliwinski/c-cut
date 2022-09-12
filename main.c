#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpuAnalyzer.h"
#include "cutThreads.h"
#include "logQueue.h"
#include "msTimer.h"
#include "sigtermHandler.h"
#include "statStructQueue.h"

cutThreads_t cutThreads;

// queues
statStructQueue_t statQueue;
logQueue_t logsQueue;
analyzerQueue_t analyzerQueue;


// other
size_t statCpuNum;
msTimer_t cutTimer;

int main()
{
  signal(SIGINT, handle_sigint);

  if (!scanProcStat(&statCpuNum))
  {
    printf("ERROR: Cannot scan /proc/stat\n");
    return EXIT_FAILURE;
  }
  initMst(&cutTimer);
  if (!initLq(&logsQueue))
  {
    printf("Log queue init fail\n");
    return EXIT_FAILURE;
  }
  if (!initSsq(&statQueue, statCpuNum))
  {
    // not gonna get called
    // LOG_CREATE(ERROR, "Stat queue init fail");
    printf("Stat queue init fail\n");
    freeLq(&logsQueue);
    return EXIT_FAILURE;
  }

  if (!initAq(&analyzerQueue, statCpuNum))
  {
    printf("Analyzer queue init fail\n");
    freeLq(&logsQueue);
    freeSsq(&statQueue);
    return EXIT_FAILURE;
  }

  if ((pthread_mutex_init(&cutThreads.reader.mutex, PTHREAD_MUTEX_NORMAL) !=
       0) ||
      (pthread_mutex_init(&cutThreads.analyzer.mutex, PTHREAD_MUTEX_NORMAL) !=
       0) ||
      (pthread_mutex_init(&cutThreads.printer.mutex, PTHREAD_MUTEX_NORMAL) !=
       0) ||
      (pthread_mutex_init(&cutThreads.watchdog.mutex, PTHREAD_MUTEX_NORMAL) !=
       0) ||
      (pthread_mutex_init(&cutThreads.logger.mutex, PTHREAD_MUTEX_NORMAL) != 0))
  {
    freeLq(&logsQueue);
    freeSsq(&statQueue);
    freeAq(&analyzerQueue);
    return EXIT_FAILURE;
  }

  cutThreads.reader.run = 1;
  cutThreads.analyzer.run = 1;
  cutThreads.printer.run = 1;
  cutThreads.watchdog.run = 1;
  cutThreads.logger.run = 1;

  pthread_create(&cutThreads.reader.thread, NULL, &readerFunc, NULL);
  pthread_create(&cutThreads.analyzer.thread, NULL, &analyzerFunc, NULL);
  pthread_create(&cutThreads.printer.thread, NULL, &printerFunc, NULL);
  pthread_create(&cutThreads.watchdog.thread, NULL, &watchdogFunc, NULL);
  pthread_create(&cutThreads.logger.thread, NULL, &loggerFunc, NULL);

  // TODO log
  LOG_CREATE(LOG, "Program starts");

  pthread_join(cutThreads.reader.thread, NULL);
  pthread_join(cutThreads.analyzer.thread, NULL);
  pthread_join(cutThreads.printer.thread, NULL);
  pthread_join(cutThreads.watchdog.thread, NULL);
  pthread_join(cutThreads.logger.thread, NULL);

  freeSsq(&statQueue);
  freeLq(&logsQueue);
  freeAq(&analyzerQueue);

  printf("\nProgram exit\n");
  return EXIT_SUCCESS;
}
