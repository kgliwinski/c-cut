#include "cutThreads.h"
#include "watchdogTimer.h"

extern cutThreads_t cutThreads;
extern watchdogTimer_t wdTimers;

static char *logInfo[4] = {"Watchdog: Reader late", "Watchdog: Analyzer late",
                           "Watchdog: Printer late", "Watchdog: Logger late"};

void *watchdogFunc(void *arg)
{
  (void)arg;
  initTimersWt(&wdTimers);
  pthread_mutex_lock(&cutThreads.watchdog.mutex);

  cutThreads.watchdog.run = 1;

  int checkResult = 0;
  while (cutThreads.watchdog.run)
  {
    checkResult = checkThreadTimesWt(&wdTimers, &cutThreads);
    if (checkResult != 0)
    {
      printf("WD ERROR\n");
      LOG_CREATE(ERROR, logInfo[checkResult + 1]);
      pthread_cancel(cutThreads.printer.thread);
      pthread_cancel(cutThreads.analyzer.thread);
      pthread_cancel(cutThreads.reader.thread);
      if (checkResult != LOGGER)
      {
        // wait for the logs to be completed (debugging)
        cutThreads.logger.run = 0;
        while (pthread_mutex_lock(&cutThreads.logger.mutex) != 0)
        {
          usleep(1000);
        }
        pthread_cancel(cutThreads.logger.thread);
      }
      pthread_cancel(cutThreads.watchdog.thread);
    }
    usleep(WATCHDOG_SLEEP_TIME);
  }
  pthread_mutex_unlock(&cutThreads.watchdog.mutex);
  return 0;
}