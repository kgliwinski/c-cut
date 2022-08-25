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
  char *buff = calloc(BUFF_SIZE, sizeof(char));
  char *tmp = calloc(TMP_SIZE, sizeof(char));

  tmp[TMP_SIZE - 1] = '\0';
  FILE *procStat;
  // str = readProcStat();
  while (1) {
    procStat = fopen("/proc/stat", "r");
    rewind(procStat);
    readProcStat(buff, tmp, procStat, &stat);
    fclose(procStat);
    sleep(SLEEP_TIME);
  }

  free(buff);
  free(tmp);

  return 0;
}