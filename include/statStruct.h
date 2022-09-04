#ifndef STAT_STRUCT_H
#define STAT_STRUCT_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "msTimer.h"

/*! \struct cpuStruct_t constains data aquired when reading the
 *  cpuN data from /proc/stat*/
typedef struct cpuStruct_t {
  unsigned long long int user;
  unsigned long long int nice;
  unsigned long long int system;
  unsigned long long int idle;
  unsigned long long int iowait;
  unsigned long long int irq;
  unsigned long long int softirq;

} cpuStruct_t;

/*! \struct statStruct_t contains data from a whole reading of /proc/stat
 *  file, with the time of the reading*/
typedef struct statStruct_t {
  time_t sampleTimeMS;
  size_t cpuNum;
  cpuStruct_t *cpu;
} statStruct_t;

/*! \brief scans the contents of /proc/stat to determine number of cpus*/
bool scanProcStat(char *buff, char *tmp, FILE *procStat, statStruct_t *stat);

/*! \brief Reads the most important contents of the /proc/stat file*/
bool readProcStat(char *buff, char *tmp, FILE *procStat, statStruct_t *stat);

/*! \brief Prints the contents of statStruct_t to the terminal, for debugging*/
void printProcStat(statStruct_t *stat);

#endif