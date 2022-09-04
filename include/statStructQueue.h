#ifndef STAT_STRUCT_QUEUE_H
#define STAT_STRUCT_QUEUE_H

#include "statStruct.h"
#include "stdbool.h"

#define MAX_QUEUE_SIZE 25

/*! \brief Simple queue (circle buffer) based on
 * https://gist.github.com/ryankurte/61f95dc71133561ed055ff62b33585f8 */
typedef struct statStructQueue_t
{
  size_t head;
  size_t tail;
  size_t maxSize;
  statStruct_t *stats;
} statStructQueue_t;

/*! \brief Allocates memory for the queue,
 *  for elements of stat size, \returns false if stat.cpuNum == 0 */
bool initSsq(statStructQueue_t *queue, statStruct_t *stat);

/*! \brief Deallocates memory of the queue,
    \returns false if stat.cpuNum == 0 */
bool freeSsq(statStructQueue_t *queue);

/*! \brief Dequeues element from queue tail, copies it to stat
 *  \returns false if queue is empty */
bool dequeueSsq(statStructQueue_t *queue, statStruct_t *stat);

/*! \brief Enqueses stat element onto the queue on the head
 *  \returns false if queue is full */
bool enqueueSsq(statStructQueue_t *queue, statStruct_t *stat);

/*! \brief \returns true if queue is empty*/
bool isEmptySsq(statStructQueue_t *queue);

#endif