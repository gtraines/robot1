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

    while (!TurretState::allFunctionChecksCompleted) {
        Indicator::alertStrobeSlow(ACTY_LED_3);
        Taskr::delayMs(1000);
    }
    while (true) {
        Taskr::delayMs(1000);
        
    }
}

void TurretTasks::functionCheckMonitor(void* pvParameters) {
    BaseType_t notifyDutyCycleSuccess = pdFALSE;
    BaseType_t clearCountOnExit = pdTRUE;
    
    uint32_t receivedValue = 0;
    uint32_t completedFunctionChecks = 0;
    
    while (notifyDutyCycleSuccess != pdTRUE) {
        
        receivedValue = ulTaskNotifyTake(clearCountOnExit, TurretTasks::functionCheckMonitorDelay);

        if (receivedValue > 0) {
            completedFunctionChecks += receivedValue;
            receivedValue = 0; // might not be necessary
        }
        if (completedFunctionChecks > 1) {
            // Notify Executive to start DutyCycle
            TurretState::allFunctionChecksCompleted = true;
            notifyDutyCycleSuccess = xTaskNotifyGive(TurretTasks::dutyCycleMonitorHandle);
        }
    }
    
    if (notifyDutyCycleSuccess == pdTRUE) {
        vTaskDelete(TurretTasks::functionCheckMonitorHandle);
    }
    else {
        Indicator::turnOnLed(ARD_STATUS_RED);
    }
    
}

void TurretTasks::dutyCycleMonitor(void* pvParameters) {
    uint32_t receivedValue = 0;

    while (!receivedValue > 0) {
        receivedValue = ulTaskNotifyTake(pdTRUE, TurretTasks::dutyCycleMonitorDelay);
    }
    
    while (true) {

        Indicator::turnOnLed(ARD_STATUS_GRN);
        Taskr::delayMs(800);
        Indicator::turnOffLed(ARD_STATUS_GRN);
        Taskr::delayMs(300);
    }
}
