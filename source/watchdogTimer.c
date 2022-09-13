#include "watchdogTimer.h"

bool compareTimeWt(msTimer_t *timer, time_t timeInMs)
{
  if (!timer->enable)
  {
    return true;
  }
  return getTimeMst(timer) <= timeInMs;
}

void initTimersWt(watchdogTimer_t *wd)
{
  initMst(&wd->readerTimer);
  initMst(&wd->analyzerTimer);
  initMst(&wd->printerTimer);
  initMst(&wd->loggerTimer);
}

int checkThreadTimesWt(watchdogTimer_t *wd, cutThreads_t *cut)
{
  if (!compareTimeWt(&wd->readerTimer,
                     READER_SLEEP_TIME / 1000 + THREAD_EXTRA_TIME) &&
      cut->reader.run)
  {
    return READER;
  }

  if (!compareTimeWt(&wd->analyzerTimer,
                     ANALYZER_SLEEP_TIME / 1000 + THREAD_EXTRA_TIME) &&
      cut->analyzer.run)
  {
    return ANALYZER;
  }

  if (!compareTimeWt(&wd->printerTimer,
                     PRINTER_SLEEP_TIME / 1000 + THREAD_EXTRA_TIME) &&
      cut->printer.run)
  {
    return PRINTER;
  }

  if (!compareTimeWt(&wd->loggerTimer,
                     LOGGER_SLEEP_TIME / 1000 + THREAD_EXTRA_TIME) &&
      cut->logger.run)
  {
    return LOGGER;
  }
  return 0;
}