//
// Created by graham on 10/17/18.
//
#include "TurretTasks.h"
#include <TurretPins.h>
#include <TurretState.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Taskr.h>
#include <Indicator.h>


TickType_t TurretTasks::functionCheckMonitorDelay = Taskr::getMillis(2000);
TickType_t TurretTasks::dutyCycleMonitorDelay = Taskr::getMillis(1000);

TaskHandle_t TurretTasks::functionCheckMonitorHandle = NULL;
TaskHandle_t TurretTasks::executiveHandle = NULL;
TaskHandle_t TurretTasks::dutyCycleMonitorHandle = NULL;

void TurretTasks::executive(void* pvParameters) {
    while (true) {
        Indicator::alertStrobeSlow(ACTY_LED_3);
        vTaskDelay(Taskr::getMillis(1000));
    }
}

void TurretTasks::functionCheckMonitor(void* pvParameters) {
    BaseType_t notifyExecutiveSuccess = pdFALSE;
    BaseType_t clearCountOnExit = pdTRUE;
    
    uint32_t receivedValue = 0;
    uint32_t completedFunctionChecks = 0;
    
    while (notifyExecutiveSuccess != pdTRUE) {
        
        receivedValue = ulTaskNotifyTake(clearCountOnExit, TurretTasks::functionCheckMonitorDelay);

        if (receivedValue > 0) {
            completedFunctionChecks += receivedValue;
            receivedValue = 0; // might not be necessary
        }
        if (completedFunctionChecks == 4) {
            // Notify Executive to start DutyCycle
            TurretState::allFunctionChecksCompleted = true;
            BaseType_t notifyExecutiveSuccess = xTaskNotifyGive(TurretTasks::dutyCycleMonitorHandle);
        }
    }
    
    vTaskDelete(TurretTasks::functionCheckMonitorHandle);
}

void TurretTasks::dutyCycleMonitor(void* pvParameters) {
    uint32_t receivedValue = 0;

    while (!receivedValue > 0) {
        receivedValue = ulTaskNotifyTake(pdTRUE, TurretTasks::dutyCycleMonitorDelay);
    }
    
    while (true) {
        // continue
        Indicator::alertStrobeFast(ACTY_LED_1);
        vTaskDelay(Taskr::getMillis(1000));
        Indicator::turnOnLed(ARD_STATUS_GRN);
        vTaskDelay(Taskr::getMillis(800));
        Indicator::turnOffLed(ARD_STATUS_GRN);
        delay(300);
    }
}
