//
// Created by graham on 10/17/18.
//

#ifndef TURRET_TURRETTASKS_H
#define TURRET_TURRETTASKS_H

#include <Arduino_FreeRTOS.h>
#include <task.h>

class TurretTasks {
public:
    static TickType_t functionCheckMonitorDelay;
    static TickType_t dutyCycleMonitorDelay;
    static TaskHandle_t functionCheckMonitorHandle;
    static TaskHandle_t executiveHandle;
    static TaskHandle_t dutyCycleMonitorHandle;
    static void executive(void* pvParameters);
    static void functionCheckMonitor(void* pvParameters);
    static void dutyCycleMonitor(void* pvParameters);
    static void notifyFunctionCheckComplete();
    static void notifyAllFunctionChecksComplete();
};


#endif //TURRET_TURRETTASKS_H
