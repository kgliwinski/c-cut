#include "logMacro.h"
#include "logQueue.h"
#include "stdlib.h"

msTimer_t cutTimer;
logQueue_t logsQueue;

int main(int argc, char **argv)
{
  
  if (!initLq(&logsQueue))
  {
    return EXIT_FAILURE;
  }
  initMst(&cutTimer);
  FILE *logFile = fopen("../tests/c-cut_logs_test.txt", "w");

  LOG_CREATE(LOG, "LOG TYPE");
  LOG_CREATE(DEBUG, "DEBUG TYPE");
  LOG_CREATE(WARNING, "WARING TYPE");
  LOG_CREATE(ERROR, "ERROR TYPE");
  int i = 0;
  while (i++ < 4)
  {
    dequeueLq(&logsQueue, logFile);

    usleep(1000);
  }
  fclose(logFile);

  if (!freeLq(&logsQueue))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}