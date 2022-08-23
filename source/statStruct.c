#include "statStruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void readProcStat()
{
    // statStruct_t tmp;
    char *buff;
    buff = malloc(10 * sizeof(char));
    memset(buff, ' ', 10);
    char *tmp;
    tmp = malloc(10 * sizeof(char));
    memset(buff, ' ', 10);
    size_t len;
    ssize_t read;
    FILE *procStat;
    procStat = fopen("/proc/stat", "r");
    rewind(procStat);

    int num[10];
    if (procStat == NULL)
    {
        // TODO return some error/assert
    }
    else
    {
        // TODO: check if three characters are necessary to determine cpu usage
        while ((feof(procStat)) != -1)
        {
            fscanf(procStat, "%s", buff);
            {
                if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0)
                {
                    fscanf(procStat, "%d %d %d %d %d %d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6], &num[7], &num[8], &num[9]);
                    printf("%s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", buff, num[0], num[1], num[2], num[3], num[4], num[5], num[6], num[7], num[8], num[9]);
                }
                else if (strcmp(strncpy(tmp, buff, 9), "processes") == 0)
                {
                    printf("Debug\n");
                }
                else
                {
                    free(tmp);
                    free(buff);
                    return;
                }
            }
        }
    }
    fclose(procStat);
}