#ifndef SIGTERM_HANDLER_H
#define SIGTERM_HANDLER_H
#include "cutThreads.h"
#include "signal.h"

extern cutThreads_t cutThreads;

bool killThread(taskVars_t* thread)
{
  thread->run = 0;
  while (pthread_mutex_lock(&thread->mutex) != 0)
  {
    printf("%d", 1);
    usleep(1000);
  }
  pthread_cancel(thread->thread);
  return true;
}

void handle_sigint(int sig)
{
  printf("\nUser signal %d\n", sig);

  killThread(&cutThreads.reader);
  killThread(&cutThreads.analyzer);
  killThread(&cutThreads.printer);
  killThread(&cutThreads.watchdog);
  killThread(&cutThreads.logger);
}

#endif