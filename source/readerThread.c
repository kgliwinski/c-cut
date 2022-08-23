#include "cutThreads.h"
#include "statStruct.h"

void *readerFunc(void *arg)
{
    printf("Reader works!\n");
    statStruct_t str;
    char buff[255];
    //str = readProcStat();
    readProcStat();
    return 0;
}