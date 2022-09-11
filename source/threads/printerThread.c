#include <unistd.h>

#include "color.h"
#include "cpuAnalyzer.h"
#include "cutThreads.h"

extern cutThreads_t cutThreads;
extern analyzerQueue_t analyzerQueue;
extern size_t statCpuNum;

void *printerFunc(void *arg)
{
  (void)arg;
  size_t i = 0, j;
  cutThreads.printer.pid = getpid();
  float *cpuPercs = calloc(statCpuNum, sizeof(float));
  printf("%s", KBLU);
  printf("CPU %5.5s|", "   ");
  for (i = 1; i < statCpuNum; ++i)
  {
    printf("CPU %lu%4.4s|", i, "   ");
  }
  printf("\n");

  char buff[15] = "";

  i = 0;
  pthread_mutex_lock(&cutThreads.printer.mutex);
  while (cutThreads.printer.run || !isEmptyAq(&analyzerQueue))
  {
    if (dequeueAq(&analyzerQueue, cpuPercs))
    {
      printf("\r");
      // TODO add color formating based on percentage
      for (j = 0; j < analyzerQueue.cpuNum; ++j)
      {
        sprintf(buff, "%0.2f%%", cpuPercs[j]);
        printf("%s", colorByCpuUse(cpuPercs[j]));
        printf("%9.9s", buff);
        printf("%s|", KBLU);
      }

      fflush(stdout);
      i++;
    }

    usleep(PRINTER_SLEEP_TIME);
  }
  printf("\n");
  printf("%s", KNRM);
  free(cpuPercs);
  pthread_mutex_unlock(&cutThreads.printer.mutex);
  return 0;
}