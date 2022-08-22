#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "cutThreads.h"

cutThreads_t cutThreads;

int main()
{
    pthread_create(&cutThreads.analyzerThread, NULL, &analyzerFunc, NULL);
    pthread_join(cutThreads.analyzerThread, NULL);
    printf("In main\n");
    return EXIT_SUCCESS;
}
