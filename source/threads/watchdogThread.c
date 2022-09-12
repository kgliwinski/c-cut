#include "cutThreads.h"

extern cutThreads_t cutThreads;

void *watchdogFunc(void *arg)
{
  (void)arg;
  cutThreads.watchdog.pid = getpid();
  pthread_mutex_lock(&cutThreads.watchdog.mutex);
  while (cutThreads.watchdog.run)
  {
    usleep(WATCHDOG_SLEEP_TIME);
  }
  pthread_mutex_unlock(&cutThreads.watchdog.mutex);
  return 0;
}