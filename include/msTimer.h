#ifndef MS_TIMER_H
#define MS_TIMER_H
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

time_t getTimeInMs();

/*! \struct msTime_t interfaces c timers to measure time
 *  in milliseconds*/
typedef struct msTimer_t
{
  time_t startTime;
  bool enable;

} msTimer_t;

void initMst(msTimer_t* timer);

time_t getTimeMst(msTimer_t* timer);

#endif