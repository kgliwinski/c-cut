#include <stdlib.h>

#include "msTimer.h"
#include "statStructQueue.h"

#define BUFF_SIZE 20
#define TMP_SIZE 4
#define TEST_NUM 10

int main(int argc, char **argv)
{
  statStructQueue_t statQueue;
  size_t statCpuNum;
  msTimer_t cutTimer;

  char *buff = calloc(BUFF_SIZE, sizeof(char));
  char *tmp = calloc(TMP_SIZE, sizeof(char));
  FILE *procStat = NULL;

  initMst(&cutTimer);

  if (!scanProcStat(&statCpuNum) || statCpuNum == 0)
  {
    return EXIT_FAILURE;
  }

  if (!initSsq(&statQueue, statCpuNum))
  {
    return EXIT_FAILURE;
  }

  statStruct_t stat[TEST_NUM], endStat[TEST_NUM];
  size_t i = 0, j;

  for (i = 0; i < TEST_NUM; ++i)
  {
    stat[i] =
        (statStruct_t){.sampleTimeMS = 0, .cpuNum = statCpuNum, .cpu = NULL};
    stat[i].cpu = calloc(stat[i].cpuNum, sizeof(cpuStruct_t));
    endStat[i] =
        (statStruct_t){.sampleTimeMS = 0, .cpuNum = statCpuNum, .cpu = NULL};
    endStat[i].cpu = calloc(endStat[i].cpuNum, sizeof(cpuStruct_t));
  }

  i = 0;
  // check /proc/stat reading and equeue function
  while (i < TEST_NUM)
  {
    if (!readProcStat(buff, tmp, procStat, &stat[i]))
    {
      return EXIT_FAILURE;
      // LOG_CREATE(ERROR, "/proc/stat not read");
    }
    else
    {
      stat[i].sampleTimeMS = getTimeMst(&cutTimer);
      if (!enqueueSsq(&statQueue, &stat[i]))
      {
        // printf("Enqueue works\n");
        // createLogLq(0, "Enqueue works!", &logsQueue, __FILE__, __LINE__);
        // LOG_CREATE(0, "Enqueue works!");
      }
      else
      {
        i++;
      }
    }
    usleep(100000);
  }

  i = 0;

  if(isEmptySsq(&statQueue))
  {
    return EXIT_FAILURE;
  }

  // compare if dequeued items are equal to enqueued
  while (i < TEST_NUM)
  {
    if (!dequeueSsq(&statQueue, &endStat[i]))
    {
      printf("%lu", i);
      return EXIT_FAILURE;
    }
    else
    {
      if (endStat[i].cpuNum != stat[i].cpuNum)
      {
        return EXIT_FAILURE;
      }
      else if (endStat[i].sampleTimeMS != stat[i].sampleTimeMS)
      {
        printf("%lu, %lu\n", endStat[i].sampleTimeMS, stat[i].sampleTimeMS);
        //return EXIT_FAILURE;
      }
      else
      {
        for (j = 0; j < stat[i].cpuNum; ++j)
        {
          if (memcmp(&stat->cpu[j], &endStat->cpu[j], sizeof(cpuStruct_t)))
          {
            return EXIT_FAILURE;
          }
        }
      }
      i++;
    }
    usleep(100000);
  }

  if(!isEmptySsq(&statQueue))
  {
    return EXIT_FAILURE;
  }

  for (i = 0; i < TEST_NUM; ++i)
  {
    free(stat[i].cpu);
    free(endStat[i].cpu);
  }
  freeSsq(&statQueue);
  return EXIT_SUCCESS;
}