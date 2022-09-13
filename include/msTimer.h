#ifndef MS_TIMER_H
#define MS_TIMER_H
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*! \return returns system time in ms */
time_t getTimeInMs();

/*! \struct msTime_t interfaces c timers to measure time
 *  in milliseconds*/
typedef struct
{
  time_t startTime;
  bool enable;

} msTimer_t;

/*! \brief Initiates timer and sets start time to 0, 
 *  enable to 1 */
void initMst(msTimer_t* timer);

/*! \returns milliseconds since timer start*/
time_t getTimeMst(msTimer_t* timer);

/*! \brief resets the timer - sets startTime to 0*/
void resetTimerMst(msTimer_t* timer);

#endif