#include "cpuAnalyzer.h"
#include "cutThreads.h"
#include "statStructQueue.h"

extern cutThreads_t cutThreads;
extern statStructQueue_t statQueue;
extern analyzerQueue_t analyzerQueue;
extern size_t statCpuNum;

void *analyzerFunc(void *arg)
{
  (void)arg;
  cutThreads.analyzerPid = getpid();
  size_t i = 0;
  while (isEmptySsq(&statQueue))
  {
    sleep(1);
  }
  statStruct_t prevStat = {
      .cpuNum = statCpuNum, .sampleTimeMS = 0, .cpu = NULL};
  prevStat.cpu = calloc(prevStat.cpuNum, sizeof(cpuStruct_t));

  statStruct_t curStat = {.cpuNum = statCpuNum, .sampleTimeMS = 0, .cpu = NULL};
  curStat.cpu = calloc(curStat.cpuNum, sizeof(cpuStruct_t));
  
  dequeueSsq(&statQueue, &prevStat);

  statStruct_t helpStat;
  // statStruct_t helpStat = {
  //     .cpuNum = statCpuNum, .sampleTimeMS = 0, .cpu = NULL};
  // helpStat.cpu = calloc(helpStat.cpuNum, sizeof(cpuStruct_t));

  float *cpuPercs = calloc(statCpuNum, sizeof(float));

  while (1)
  {
    if (dequeueSsq(&statQueue, &curStat))
    {
      calculateAllCpus(&prevStat, &curStat, &analyzerQueue, cpuPercs);
      //  manipulating the memory not to copy whole structures
      helpStat = curStat;
      curStat = prevStat;
      prevStat = helpStat;
      // TODO usrednianie
      i++;
    }
    usleep(ANALYZER_SLEEP_TIME);
  }
  free(prevStat.cpu);
  free(curStat.cpu);
  // free(helpStat.cpu);
  return 0;
}