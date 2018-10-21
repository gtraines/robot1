#ifndef TASKR_H
#define TASKR_H

#include <Arduino_FreeRTOS.h>
#include <task.h>

class Taskr
{
public:
    static TickType_t getMillis(int millisToConvert);
    static void delayMs(int millisToConvert);
};

#endif // TASKR_H
