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