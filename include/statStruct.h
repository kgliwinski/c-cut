#ifndef STAT_STRUCT_H
#define STAT_STRUCT_H
#include <stdio.h>

/*! \struct cpuStruct_t constains data aquired when reading the
 *  cpuN data from /proc/stat*/
typedef struct cpuStruct_t{
    unsigned long long int user;
    unsigned long long int nice;
    unsigned long long int system;
    unsigned long long int idle;
    unsigned long long int iowait;
    unsigned long long int irq;
    unsigned long long int softirq; 

}cpuStruct_t;


typedef struct statStruct_t{
    unsigned long long int sampleTimeMS;
    cpuStruct_t cpu[];
}statStruct_t;

void readProcStat(char *buff, char *tmp, FILE *procStat, statStruct_t *stat);

#endif