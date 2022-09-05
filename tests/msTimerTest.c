#include <stdio.h>

#include "../include/msTimer.h"

int main(int argc, char **argv)
{
  int sleepTime_us = 10000;
  size_t i = 0;
  msTimer_t timer;
  initMst(&timer);
  for (; i < 100; ++i)
  {
    // approximates the runtime of other functions in the scope, thus adds some
    // constants
    if (!(getTimeMst(&timer) <=
              ((time_t)i * (sleepTime_us / 1000 + sleepTime_us / 10000) + 1) &&
          getTimeMst(&timer) >=
              ((time_t)i * (sleepTime_us / 1000 - sleepTime_us / 10000) - 1)))
    {
      return 1;
    }
    printf("%lu\n", getTimeMst(&timer));
    usleep(sleepTime_us);
  }

  if (timer.enable != 1)
  {
    return 1;
  }

  return 0;
}