#ifndef COLOR_H
#define COLOR_H

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

char* colorByCpuUse(float cpuUse)
{
    if(cpuUse <= 20.0f)
    {
        return KCYN;
    }
    else if(cpuUse <= 50.0f)
    {
        return KBLU;
    }
    else if(cpuUse <= 80.0f)
    {
        return KYEL;
    }
    else if(cpuUse <= 100.0f)
    {
        return KRED;
    }
    return KNRM;
}

#endif