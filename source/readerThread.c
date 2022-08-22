#include "cutThreads.h"

void *readerFunc(void *arg)
{
    printf("Reader works!\n");

    FILE *procStat;
    char buff[255];
    // TODO use strtok
    procStat = fopen("/proc/123/stat", "r");
    if (procStat == NULL)
    {
        return 0;
    }
    else
    {
        fscanf(procStat, "%s", buff);
        printf("1 : %s\n", buff);
    }

    return 0;
}