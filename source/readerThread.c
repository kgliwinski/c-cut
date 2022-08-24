#include "cutThreads.h"
#include "statStruct.h"
#include <stdlib.h>
#include <stdio.h>

const size_t buffSize = 20;
const size_t tmpSize = 4;

void *readerFunc(void *arg)
{
    printf("Reader works!\n");
    statStruct_t str;
    size_t i = 0;
    char *buff = calloc(buffSize, sizeof(char));
    char *tmp = calloc(tmpSize, sizeof(char));

    tmp[tmpSize - 1] = '\0';
    FILE *procStat;
    procStat = fopen("/proc/stat", "r");

    // str = readProcStat();
    readProcStat(buff, tmp, procStat);

    free(buff);
    free(tmp);
    fclose(procStat);
    return 0;
}