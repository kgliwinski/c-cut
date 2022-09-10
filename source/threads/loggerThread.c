#include <stdio.h>

#include "cutThreads.h"
#include "logQueue.h"

extern cutThreads_t cutThreads;
extern logQueue_t logsQueue;

void *loggerFunc(void *arg)
{
  (void)arg;
  cutThreads.loggerPid = getpid();
  size_t i = 0;
  FILE *logFile = fopen("../c-cut_logs.txt", "w");
  while (1)
  {
    if (dequeueLq(&logsQueue, logFile))
    {
      i++;
    }
    sleep(1);
  }
  fclose(logFile);
  return 0;
}