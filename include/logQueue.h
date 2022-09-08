#ifndef LOGS_QUEUE_H
#define LOGS_QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_LOGS_QUEUE_SIZE 25
#define MAX_LOGS_LENGTH 255



/*! \enum logTypes contains different log codes,
 *  used with logTypeText char array located in \file logQueue.c */
enum logTypes
{
  LOG = 0,
  DEBUG,
  WARNING,
  ERROR
};

/*! \struct logQueue_t constains array of strings to be saved*/
typedef struct
{
  size_t head;
  size_t tail;
  size_t maxSize;
  char **logs;
} logQueue_t;

/*! \brief Creates a log string and puts it on a logQueue*/
void createLogLq(int logType, char *msg, logQueue_t *queue, const char *file,
                 const int line);

/*! \brief Allocates memory for the queue,
 *  for elements of stat size, \returns false if stat.cpuNum == 0 */
bool initLq(logQueue_t *queue);

/*! \brief Deallocates memory of the queue,
    \returns false if //TODO */
bool freeLq(logQueue_t *queue);

/*! \brief Dequeues element from queue tail, prints it to file
 *  \returns false if file is not open, or queue is empty */
bool dequeueLq(logQueue_t *queue, FILE *logFile);

/*! \brief Enqueses log element onto the queue on the head
 *  \returns false if queue is full */
bool enqueueLq(logQueue_t *queue, char *log);

/*! \brief \returns true if queue is empty*/
bool isEmptyLq(logQueue_t *queue);



#endif