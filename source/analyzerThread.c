#include "cutThreads.h"
#include "statStructQueue.h"

void *analyzerFunc(void *arg)
{
    (void) arg;
    printf("Analyzer works!\n");
    return 0;
}