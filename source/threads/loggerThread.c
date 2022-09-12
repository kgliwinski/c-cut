#include <stdio.h>

#include "cutThreads.h"
#include "logQueue.h"


extern cutThreads_t cutThreads;
extern logQueue_t logsQueue;

extern watchdogStruct_t wd;

void *loggerFunc(void *arg)
{
  pthread_mutex_lock(&cutThreads.logger.mutex);
  (void)arg;
  cutThreads.logger.pid = getpid();
  FILE *logFile = fopen("../c-cut_logs.txt", "w");
  wd.loggerPtr.logFile = logFile;

  wd.freeLogger = 0;
  while (cutThreads.logger.run || !isEmptyLq(&logsQueue))
  {

    if (dequeueLq(&logsQueue, logFile))
    {
    }
    if (isEmptyLq(&logsQueue))
    {
    }

    usleep(LOGGER_SLEEP_TIME);
  }
  fclose(logFile);
  wd.freeLogger = 1;
  pthread_mutex_unlock(&cutThreads.logger.mutex);
  return 0;
}