#ifndef CUT_THREADS_H
#define CUT_THREADS_H
#include <pthread.h>
#include <stdio.h>

#include "logMacro.h"

/*! \file Contains definitions for thread functions */

// Sleep times (in us)
#define READER_SLEEP_TIME 100000    // 100ms
#define ANALYZER_SLEEP_TIME 100000  // 100ms

/*! \typedef cutThreads_t Contains pthread_t objects as well as memory buffors
 *  necessary in the programs execution*/
typedef struct cutThreads_t
{
  pthread_t readerThread;
  pthread_t analyzerThread;
  pthread_t printerThread;
  pthread_t watchdogThread;
  pthread_t loggerThread;

} cutThreads_t;

/*! \brief Reads the contents of /proc/stat file and sends
    the contents to analyzer thread */
void *readerFunc(void *arg);

/*! \brief Analyzes data sent by reader thread and calculates CPU usage,
 *   which it is sent to printer thread*/
void *analyzerFunc(void *arg);

/*! \brief Formats and prints the average CPU usage per second*/
void *printerFunc(void *arg);

/*! \brief Monitors the execution of the program, checks if other threads are
 * out of control or have stopped operating */
void *watchdogFunc(void *arg);

/*! \brief Gathers debug data from all other threads, formats them and saves
 *  data in other file*/
void *loggerFunc(void *arg);

#endif
