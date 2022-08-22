#include "cutThreads.h"

void *printerFunc(void *arg)
{
    printf("Printer works!\n");
    return 0;
}