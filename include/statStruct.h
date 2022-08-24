#ifndef STAT_STRUCT_H
#define STAT_STRUCT_H
#include <stdio.h>

typedef struct cpuStruct_t{
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq; 
}cpuStruct_t;

typedef struct statStruct_t{
    int ctxt;
    int btime;
    cpuStruct_t cpu[];
}statStruct_t;

void readProcStat(char *buff, char *tmp, FILE *procStat);

#endif