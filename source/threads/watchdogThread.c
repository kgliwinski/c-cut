#include "cutThreads.h"

extern cutThreads_t cutThreads;

void *watchdogFunc(void *arg)
{
    (void) arg;
    cutThreads.watchdogPid = getpid();
    return 0;
}