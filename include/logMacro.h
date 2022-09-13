#ifndef LOG_MACRO_H
#define LOG_MACRO_H

#include "logQueue.h"
#include "msTimer.h"

extern logQueue_t logsQueue;
extern msTimer_t cutTimer;
// TODO add time of log

/*! \brief creates log and puts it on the logsQueue
    \param logType int indicating the log type (0-3)
    \param msg string for the message stored in log */
#define LOG_CREATE(logType, msg)                                         \
  createLogLq(getTimeMst(&cutTimer), logType, msg, &logsQueue, __FILE__, \
              __LINE__)

#endif