#ifndef CPU_ANALYZER_H
#define CPU_ANALYZER_H

#include "statStruct.h"

#define MAX_ANALYZER_QUEUE_SIZE 25

/*! \brief calculates cpu usage
 *  \returns usage in percentage */
float calculateCpuUsePerc(cpuStruct_t prevCpu, cpuStruct_t curCpu);

typedef struct
{
  size_t head;
  size_t tail;
  size_t maxSize;
  size_t cpuNum;
  float **cpuPerc;
} analyzerQueue_t;

/*! \brief Allocates memory for the queue,
 *  for elements of stat size, \returns false if stat.cpuNum == 0 */
bool initAq(analyzerQueue_t *queue, size_t cpuNum);

/*! \brief Deallocates memory of the queue,
    \returns false if //TODO */
bool freeAq(analyzerQueue_t *queue);

/*! \brief Dequeues element from queue tail, copies it to cpus array
 *  \returns false if file is not open, or queue is empty */
bool dequeueAq(analyzerQueue_t *queue, float *cpus);

/*! \brief Enqueses log element onto the queue on the head
 *  \returns false if queue is full */
bool enqueueAq(analyzerQueue_t *queue, float *cpus);

/*! \brief \returns true if queue is empty*/
bool isEmptyAq(analyzerQueue_t *queue);

/*! \brief calculates cpu usage of all cpus in /proc/stat
 *  Puts it on the logQueue */
bool calculateAllCpus(statStruct_t *prevStat, statStruct_t *curStat,
                      analyzerQueue_t *queue, float *cpuPercs);

#endif