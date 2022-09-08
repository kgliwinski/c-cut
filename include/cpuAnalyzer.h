#ifndef CPU_ANALYZER_H
#define CPU_ANALYZER_H

#include "statStruct.h"

/*! \brief calculates cpu usage
 *  \returns usage in percentage */
float calculateCpuUsePerc(cpuStruct_t prevCpu, cpuStruct_t curCpu);

#endif