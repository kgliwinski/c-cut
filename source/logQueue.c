#include "logQueue.h"

static const char* logTypeText[4] = {"LOG", "DEBUG", "WARNING", "ERROR"};

void createLogLq(int logType, char* msg, logQueue_t* queue)
{
  char logText[MAX_LOGS_LENGTH];
  if (sprintf(logText, "Log Type: %s;Log message: %s; At file: %s; Line: %d\n",
              logTypeText[logType], msg, __FILE__, __LINE__) >= 0)
  {
    printf("%s", logText);
    printf("%ld\n", strlen(logText));
    enqueueLq(queue, logText);
  }
}

bool initLq(logQueue_t* queue)
{
  if (MAX_LOGS_LENGTH == 0 || MAX_LOGS_QUEUE_SIZE == 0)
  {
    return false;
  }
  size_t i = 0;
  *queue = (logQueue_t){0, 0, MAX_LOGS_QUEUE_SIZE,
                        malloc(MAX_LOGS_QUEUE_SIZE * sizeof(char*))};
  for (; i < MAX_LOGS_QUEUE_SIZE; ++i)
  {
    queue->logs[i] = calloc(MAX_LOGS_LENGTH, sizeof(char));
  }
  return true;
}

bool freeLq(logQueue_t *queue)
{
  size_t i = 0;
  for (; i < MAX_LOGS_QUEUE_SIZE; ++i)
  {
    free(queue->logs[i]);
  }
  free(queue->logs);
  return true;
}

bool enqueueLq(logQueue_t* queue, char* log)
{
  if (((queue->head + 1) % queue->maxSize) == queue->tail)
  {
    return false;
  }
  memcpy(queue->logs[queue->head], log, strlen(log) * sizeof(char));
  queue->head = (queue->head + 1) % queue->maxSize;
  return true;
}

bool isEmptyLq(logQueue_t* queue) { return (queue->head == queue->tail); }