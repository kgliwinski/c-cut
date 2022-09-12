#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdbool.h>
#include <stdio.h>

#include "statStruct.h"

typedef struct
{
  struct
  {
    char *buff;
    char *tmp;
    FILE *procStat;
    statStruct_t *stat;
  } readerPtr;

  struct
  {
    statStruct_t *prevStat;
    statStruct_t *curStat;
    float *cpuPercs;
    float *cpuSum;
  } analyzerPtr;

  struct
  {
    float *cpuPercs;
  } printerPtr;

  struct
  {
    FILE *logFile;
  } loggerPtr;

  bool freeReader;
  bool freeAnalyzer;
  bool freePrinter;
  bool freeLogger;

} watchdogStruct_t;

/*! \brief Checks if there are resources to be deallocated inside
 *          readerThread and frees them if the tasks are inactive */
void freeReader(watchdogStruct_t *watchdog);

/*! \brief Checks if there are resources to be deallocated inside
 *          analyzerThread and frees them if the tasks are inactive */
void freeAnalyzer(watchdogStruct_t *watchdog);

/*! \brief Checks if there are resources to be deallocated inside
 *          printerThread and frees them if the tasks are inactive */
void freePrinter(watchdogStruct_t *watchdog);

/*! \brief Checks if there are resources to be deallocated inside
 *          loggerThread and frees them if the tasks are inactive */
void freeLogger(watchdogStruct_t *watchdog);

#endif