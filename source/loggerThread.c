#include "cutThreads.h"
#include "logQueue.h"

extern logQueue_t logsQueue;

void *loggerFunc(void *arg)
{
  (void)arg;
  size_t i = 0;
  printf("Logger works!\n");
  while (i++ < 3)
  {
    createLogLq(0, "NIC", &logsQueue);
    sleep(1);
  }
  return 0;
}