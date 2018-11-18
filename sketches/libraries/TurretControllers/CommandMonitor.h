//
// Created by graham on 11/12/18.
//

#ifndef TURRET_COMMANDMONITOR_H
#define TURRET_COMMANDMONITOR_H


#include <Arduino_FreeRTOS.h>
class CommandMonitor {
public:
    static void dutyCycle(void* pvParameters);
    static TaskHandle_t commandMonitorTaskHandle;
};


#endif //TURRET_COMMANDMONITOR_H
