//
// Created by graham on 10/17/18.
//

#ifndef TURRET_TURRETTASKS_H
#define TURRET_TURRETTASKS_H

#include <Arduino_FreeRTOS.h>
#include <task.h>

class TurretTasks {
public:
    static TaskHandle_t DemoMonitorTask;

};


#endif //TURRET_TURRETTASKS_H
