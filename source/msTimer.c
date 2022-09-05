#include "../include/msTimer.h"

static struct timespec time_s;

time_t getTimeInMs()
{
  clock_gettime(CLOCK_MONOTONIC_RAW, &time_s);
  return time_s.tv_sec * 1000 + time_s.tv_nsec / 1000000;
}

void initMst(msTimer_t* timer) 
{
    
    timer->startTime = getTimeInMs();
    timer->enable = true;
}

time_t getTimeMst(msTimer_t* timer)
{
    return getTimeInMs() - timer->startTime;
}