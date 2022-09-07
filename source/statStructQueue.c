#include "statStructQueue.h"

bool initSsq(statStructQueue_t *queue, statStruct_t *stat)
{
  if (stat->cpuNum == 0)
  {
    return false;
  }
  size_t i = 0;
  *queue = (statStructQueue_t){0, 0, MAX_STAT_QUEUE_SIZE,
                               malloc(MAX_STAT_QUEUE_SIZE * sizeof(statStruct_t))};
  for (i = 0; i < MAX_STAT_QUEUE_SIZE; ++i)
  {
    queue->stats[i].cpu = calloc(stat->cpuNum, sizeof(cpuStruct_t));
  }
  return true;
}

bool freeSsq(statStructQueue_t *queue)
{
  size_t i = 0;
  for (; i < MAX_STAT_QUEUE_SIZE; ++i)
  {
    free(queue->stats[i].cpu);
  }
  free(queue->stats);
  return true;
}

bool dequeueSsq(statStructQueue_t *queue, statStruct_t *stat)
{
  if (isEmptySsq(queue))
  {
    return false;
  }
  stat->sampleTimeMS = queue->stats[queue->tail].sampleTimeMS;
  stat->cpuNum = queue->stats[queue->tail].cpuNum;
  memcpy(stat->cpu, queue->stats[queue->tail].cpu,
         stat->cpuNum * sizeof(cpuStruct_t));
  queue->tail = (queue->tail + 1) % queue->maxSize;
  return true;
}

bool enqueueSsq(statStructQueue_t *queue, statStruct_t *stat)
{
  if (((queue->head + 1) % queue->maxSize) == queue->tail)
  {
    return false;
  }
  queue->stats[queue->head].sampleTimeMS = stat->sampleTimeMS;
  queue->stats[queue->head].cpuNum = stat->cpuNum;
  memcpy(queue->stats[queue->head].cpu, stat->cpu,
         queue->stats[queue->head].cpuNum * sizeof(cpuStruct_t));
  queue->head = (queue->head + 1) % queue->maxSize;
  return true;
}

bool isEmptySsq(statStructQueue_t *queue)
{
  return (queue->head == queue->tail);
}