#include "watchdogStruct.h"

void freeReader(watchdogStruct_t *watchdog)
{
  if (!watchdog->freeReader)
  {
    free(watchdog->readerPtr.buff);
    free(watchdog->readerPtr.tmp);
    free(watchdog->readerPtr.stat);
    if (watchdog->readerPtr.procStat != NULL)
    {
      fclose(watchdog->readerPtr.procStat);
    }
  }
}

void freeAnalyzer(watchdogStruct_t *watchdog)
{
  if (!watchdog->freeAnalyzer)
  {
    free(watchdog->analyzerPtr.prevStat);
    free(watchdog->analyzerPtr.curStat);
    free(watchdog->analyzerPtr.cpuPercs);
    free(watchdog->analyzerPtr.cpuSum);
  }
}

void freePrinter(watchdogStruct_t *watchdog)
{
  if (!watchdog->freePrinter)
  {
    free(watchdog->printerPtr.cpuPercs);
  }
}

void freeLogger(watchdogStruct_t *watchdog)
{
  if (!watchdog->freeLogger)
  {
    if (watchdog->loggerPtr.logFile != NULL)
    {
      fclose(watchdog->loggerPtr.logFile);
    }
  }
}