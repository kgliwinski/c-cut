#ifndef SIGTERM_HANDLER_H
#define SIGTERM_HANDLER_H
#include "signal.h"
#include "cutThreads.h"

extern cutThreads_t cutThreads;

void handle_sigint(int sig)
{
    //printf("Caught signal%d\n", sig);
    pthread_kill(cutThreads.readerThread, sig);
    pthread_kill(cutThreads.analyzerThread, sig);
    pthread_kill(cutThreads.printerThread, sig);
    pthread_kill(cutThreads.watchdogThread, sig);
    pthread_kill(cutThreads.loggerThread, sig);
    pthread_cancel(cutThreads.readerThread);
    pthread_cancel(cutThreads.analyzerThread);
    pthread_cancel(cutThreads.printerThread);
    pthread_cancel(cutThreads.watchdogThread);
    pthread_cancel(cutThreads.loggerThread);
}

#endif