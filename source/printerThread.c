#include "cutThreads.h"
#include <unistd.h>
void *printerFunc(void *arg)
{
    printf("Printer works!\n");
    while(1)
    {
        printf("Test sleep\n");
        sleep(1);
    }
    return 0;
}