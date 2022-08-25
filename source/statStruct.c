#include "statStruct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void readProcStat(char *buff, char *tmp, FILE *procStat, statStruct_t *stat) {
  size_t i = 0;

  if (procStat == NULL) {
    // TODO return some error/assert
  } else {
    while ((feof(procStat)) != -1) {
      fscanf(procStat, "%s", buff);
      {
        if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0) {
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
        } else {
          return;
        }
      }
    }
  }
  return;
}