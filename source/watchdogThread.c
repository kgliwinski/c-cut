#include "cutThreads.h"

void *watchdogFunc(void *arg)
{
    printf("Watchdog works!\n");
    return 0;
}