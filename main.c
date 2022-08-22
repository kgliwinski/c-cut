#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "cutThreads.h"

cutThreads_t cutThreads;

int main()
{
    pthread_create(&cutThreads.readerThread, NULL, &readerFunc, NULL);
    pthread_create(&cutThreads.analyzerThread, NULL, &analyzerFunc, NULL);
    pthread_create(&cutThreads.printerThread, NULL, &printerFunc, NULL);
    pthread_create(&cutThreads.watchdogThread, NULL, &watchdogFunc, NULL);
    pthread_create(&cutThreads.loggerThread, NULL, &loggerFunc, NULL);

    pthread_join(cutThreads.readerThread, NULL);
    pthread_join(cutThreads.analyzerThread, NULL);
    pthread_join(cutThreads.printerThread, NULL);
    pthread_join(cutThreads.watchdogThread, NULL);
    pthread_join(cutThreads.loggerThread, NULL);
    
    printf("In main\n");
    return EXIT_SUCCESS;
}
