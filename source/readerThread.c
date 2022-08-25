#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cutThreads.h"
#include "statStruct.h"

#define BUFF_SIZE 20
#define TMP_SIZE 4
#define SLEEP_TIME 1.0f

void *readerFunc(void *arg) {
  (void)arg;  // to hide the unused parameter warning
  printf("Reader works!\n");
  statStruct_t stat;
  struct timespec time;
  char *buff = calloc(BUFF_SIZE, sizeof(char));
  char *tmp = calloc(TMP_SIZE, sizeof(char));

  tmp[TMP_SIZE - 1] = '\0';
  FILE *procStat;
  // str = readProcStat();
  while (1) {
    procStat = fopen("/proc/stat", "r");
    // measure sample time
    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
    stat.sampleTimeMS = time.tv_sec * 1000000 + time.tv_sec / 1000;
    rewind(procStat);
    readProcStat(buff, tmp, procStat, &stat);
    fclose(procStat);
    sleep(SLEEP_TIME);
  }

  free(buff);
  free(tmp);

  return 0;
}