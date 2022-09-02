#include "statStructQueue.h"

/*
void* queue_read(queue_t *queue) {
    if (queue->tail == queue->head) {
        return NULL;
    }
    void* handle = queue->data[queue->tail];
    queue->data[queue->tail] = NULL;
    queue->tail = (queue->tail + 1) % queue->size;
    return handle;
}

int queue_write(queue_t *queue, void* handle) {
    if (((queue->head + 1) % queue->size) == queue->tail) {
        return -1;
    }
    queue->data[queue->head] = handle;
    queue->head = (queue->head + 1) % queue->size;
    return 0;
}
*/
bool dequeue(statStructQueue_t *queue, statStruct_t *stat)
{
  if (isEmpty(queue))
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

bool enqueue(statStructQueue_t *queue, statStruct_t *stat)
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

bool isEmpty(statStructQueue_t *queue) { return (queue->head == queue->tail); }