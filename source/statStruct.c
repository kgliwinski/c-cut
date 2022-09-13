#include "statStruct.h"

bool scanProcStat(size_t *cpuNum)
{
  FILE *procStat;
  if ((procStat = fopen("/proc/stat", "r")) == NULL)
  {
    return false;
  }
  rewind(procStat);
  *cpuNum = 0;
  char buff[25] = "";
  char tmp[4] = "";
  tmp[3] = '\0';
  while ((feof(procStat)) != -1)
  {
    if (fscanf(procStat, "%s", buff) != 1)
    {
      return false;
    }

    if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0)
    {
      // skip whole line
      if (fscanf(procStat, "%*[^\n]\n") != 0)
      {
        return false;
      }
      (*cpuNum)++;
    }
    else
    {
      fclose(procStat);
      return true;
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
    if (fscanf(procStat, "%s", buff) != 1)
    {
      return false;
    }

    if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0)
    {
      // read first seven numbers of each cpu
      if (fscanf(procStat,
                 "%llu %llu %llu %llu %llu %llu %llu %llu %llu %llu%*[^\n]\n",
                 &stat->cpu[i].user, &stat->cpu[i].nice, &stat->cpu[i].system,
                 &stat->cpu[i].idle, &stat->cpu[i].iowait, &stat->cpu[i].irq,
                 &stat->cpu[i].softirq, &stat->cpu[i].steal,
                 &stat->cpu[i].guest, &stat->cpu[i].guest_nice) != 10)
      {
        return false;
      }
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
  fclose(procStat);
  return true;
}

void printProcStat(statStruct_t *stat)
{
  printf("TIME: %lu\n", stat->sampleTimeMS);
  for (size_t i = 0; i < stat->cpuNum; ++i)
  {
    printf(
        "CPU%lu: %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu \n",
        i, stat->cpu[i].user, stat->cpu[i].nice, stat->cpu[i].system,
        stat->cpu[i].idle, stat->cpu[i].iowait, stat->cpu[i].irq,
        stat->cpu[i].softirq, stat->cpu[i].steal, stat->cpu[i].guest,
        stat->cpu[i].guest_nice);
  }
}