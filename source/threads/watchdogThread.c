#include "cutThreads.h"
#include "watchdogTimer.h"

extern cutThreads_t cutThreads;
extern watchdogTimer_t wdTimers;

static char *logInfo[4] = {"Watchdog: Reader late", "Watchdog: Analyzer late",
                           "Watchdog: Printer late", "Watchdog: Logger late"};

void *watchdogFunc(void *arg)
{
  (void)arg;
  cutThreads.watchdog.pid = getpid();
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
    }
    usleep(WATCHDOG_SLEEP_TIME);
  }
  pthread_mutex_unlock(&cutThreads.watchdog.mutex);
  return 0;
}