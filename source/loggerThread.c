#include "cutThreads.h"

void *loggerFunc(void *arg)
{
    (void) arg;
    printf("Logger works!\n");
    return 0;
}