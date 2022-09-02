#include "cutThreads.h"
#include <unistd.h>
void *printerFunc(void *arg)
{
    int i = 0;
    (void)arg;
    printf("Printer works!\n");
    while(i++<3)
    {
        printf("Test sleep\n");
        sleep(1);
    }
    return 0;
}