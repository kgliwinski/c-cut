#ifndef WATCHDOG_TIMER_H
#define WATCHDOG_TIMER_H
#include <stdbool.h>

#include "cutThreads.h"
#include "msTimer.h"

#define THREAD_EXTRA_TIME 100  // ms

enum threads {
    READER = 1,
    ANALYZER,
    PRINTER,
    LOGGER
};

typedef struct
{
  msTimer_t readerTimer;
  msTimer_t analyzerTimer;
  msTimer_t printerTimer;
  msTimer_t loggerTimer;

} watchdogTimer_t;

/*! \brief compares the timer value with \param timeInMs
 *  \returns true if timer value if timer value is lower that timeInMs
 *  \returns true otherwise or if the timer is not enabled
 */
bool compareTimeWt(msTimer_t *timer, time_t timeInMs);

/*! \brief Initiates all timers from watchdogTimer_t */
void initTimersWt(watchdogTimer_t *wd);

/*! \brief checks if any thread exceeded loop time
 *  \returns false if any exceeds the specified loop time
 *            which is equal to eachs sleeptime + THREAD_EXTRA_TIME,
 *            AND if the threads are currently running
 */
int checkThreadTimesWt(watchdogTimer_t *wd, cutThreads_t *cut);

#endif