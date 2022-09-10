#include "cpuAnalyzer.h"

float calculateCpuUsePerc(cpuStruct_t prevCpu, cpuStruct_t curCpu)
{
  unsigned long long int prevIdle = prevCpu.idle + prevCpu.iowait;
  unsigned long long int curIdle = curCpu.idle + curCpu.iowait;

  unsigned long long int prevNonIdle = prevCpu.user + prevCpu.nice +
                                       prevCpu.system + prevCpu.irq +
                                       prevCpu.softirq + prevCpu.steal;
  unsigned long long int curNonIdle = curCpu.user + curCpu.nice +
                                      curCpu.system + curCpu.irq +
                                      curCpu.softirq + curCpu.steal;

  unsigned long long int prevTotal = prevIdle + prevNonIdle;
  unsigned long long int curTotal = curIdle + curNonIdle;

  unsigned long long int totald = curTotal - prevTotal;
  unsigned long long int idled = curIdle - prevIdle;

  return ((float)totald - (float)idled) / (float)totald * 100.0f;
}

bool initAq(analyzerQueue_t *queue, size_t cpuNum)
{
  if (MAX_ANALYZER_QUEUE_SIZE == 0)
  {
    return false;
  }
  size_t i = 0;
  *queue = (analyzerQueue_t){0, 0, MAX_ANALYZER_QUEUE_SIZE, cpuNum,
                             malloc(MAX_ANALYZER_QUEUE_SIZE * sizeof(float *))};
  for (; i < MAX_ANALYZER_QUEUE_SIZE; ++i)
  {
    queue->cpuPerc[i] = calloc(cpuNum, sizeof(float));
  }
  return true;
}

bool freeAq(analyzerQueue_t *queue)
{
  size_t i = 0;
  for (; i < MAX_ANALYZER_QUEUE_SIZE; ++i)
  {
    free(queue->cpuPerc[i]);
  }
  free(queue->cpuPerc);
  return true;
}

bool dequeueAq(analyzerQueue_t *queue, float *cpus)
{
  if (isEmptyAq(queue))
  {
    return false;
  }
  memcpy(cpus, queue->cpuPerc[queue->tail], queue->cpuNum * sizeof(float));
  queue->tail = (queue->tail + 1) % queue->maxSize;
  return true;
}

bool enqueueAq(analyzerQueue_t *queue, float *cpus)
{
  if (((queue->head + 1) % queue->maxSize) == queue->tail)
  {
    return false;
  }
  memcpy(queue->cpuPerc[queue->head], cpus, queue->cpuNum * sizeof(float));
  queue->head = (queue->head + 1) % queue->maxSize;
  return true;
}

bool isEmptyAq(analyzerQueue_t *queue) { return (queue->head == queue->tail); }

bool calculateAllCpus(statStruct_t *prevStat, statStruct_t *curStat,
                      analyzerQueue_t *queue, float *cpuPercs)
{
  bool exit = true;
  if(prevStat->cpuNum != curStat->cpuNum)
  {
    return false;
  }
  size_t i = 0;
  for(; i < queue->cpuNum; ++i)
  {
    cpuPercs[i] = calculateCpuUsePerc(prevStat->cpu[i], curStat->cpu[i]);
    //printf("%f", cpuPercs[i]);
  }
  exit = enqueueAq(queue, cpuPercs);
  return exit;
}