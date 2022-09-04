#include "statStruct.h"

bool scanProcStat(char *buff, char *tmp, FILE *procStat, statStruct_t *stat)
{
  if ((procStat = fopen("/proc/stat", "r")) == NULL)
  {
    return false;
  }
  rewind(procStat);
  stat->cpuNum = 0;

  while ((feof(procStat)) != -1)
  {
    fscanf(procStat, "%s", buff);
    {
      if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0)
      {
        // read first seven numbers of each cpu
        fscanf(procStat, "%*[^\n]\n");
        stat->cpuNum++;
      }
      else
      {
        fclose(procStat);
        return true;
      }
    }
  }

  fclose(procStat);

  return true;
}

bool readProcStat(char *buff, char *tmp, FILE *procStat, statStruct_t *stat)
{
  if ((procStat = fopen("/proc/stat", "r")) == NULL)
  {
    return false;
  }
  size_t i = 0;
  rewind(procStat);

  while ((feof(procStat)) != -1)
  {
    fscanf(procStat, "%s", buff);
    {
      if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0)
      {
        // read first seven numbers of each cpu
        fscanf(procStat, "%llu %llu %llu %llu %llu %llu %llu %*[^\n]\n",
               &stat->cpu[i].user, &stat->cpu[i].nice, &stat->cpu[i].system,
               &stat->cpu[i].idle, &stat->cpu[i].iowait, &stat->cpu[i].irq,
               &stat->cpu[i].softirq);
        /*printf("%s, %llu, %llu, %llu, %llu, %llu, %llu, %llu,\n", buff,
               stat->cpu[i].user, stat->cpu[i].nice, stat->cpu[i].system,
               stat->cpu[i].idle, stat->cpu[i].iowait, stat->cpu[i].irq,
               stat->cpu[i].softirq);*/
        i++;
      }
      else
      {
        fclose(procStat);
        return true;
      }
    }
  }
  fclose(procStat);
  return true;
}

void printProcStat(statStruct_t *stat)
{
  printf("TIME: %llu\n", stat->sampleTimeMS);
  for (size_t i = 0; i < stat->cpuNum; ++i)
  {
    printf("CPU%lu: %llu, %llu, %llu, %llu, %llu, %llu, %llu\n", i,
           stat->cpu[i].user, stat->cpu[i].nice, stat->cpu[i].system,
           stat->cpu[i].idle, stat->cpu[i].iowait, stat->cpu[i].irq,
           stat->cpu[i].softirq);
  }
}